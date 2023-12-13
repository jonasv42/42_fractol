/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <jvets@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:27:28 by jvets             #+#    #+#             */
/*   Updated: 2023/12/12 23:20:45 by jvets            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	main(int argc, char *argv[])
{
	t_specs	specs;

	if (!check_params(argc, argv, &specs))
		return (EXIT_FAILURE);
		
	specs.mlx = mlx_init(WIDTH, HEIGHT, specs.fractol, true); //connect to x server
	if (!specs.mlx)
		return (EXIT_FAILURE);

	specs.img = mlx_new_image(specs.mlx, WIDTH, HEIGHT);
	if (!specs.img)
		return (EXIT_FAILURE);
	
	specs.draw(&specs);
		
	if (!specs.img || (mlx_image_to_window(specs.mlx, specs.img, 0, 0) < 0))
		ft_printf("Error");

	mlx_key_hook(specs.mlx, &esc, &specs);
	//mlx_scroll_hook(mlx, ft_scroll, &specs);
	mlx_loop(specs.mlx);
	mlx_terminate(specs.mlx);
	return (0);
}

void	draw_julia(t_specs *specs)
{
	double		w;
	double		h;
	t_complex	c_plane; //complex plane
	int			iterations;

	h = 0;
	while (h < 800)
	{
		w = 0;
		while (w < 800)
		{
			c_plane = pixel_to_complex(w, h);
			iterations = calculate_infinity(c_plane, &specs);
			if (iterations > 0)
				mlx_put_pixel(specs->img, w, h, color_progression(iterations));
			else
				mlx_put_pixel(specs->img, w, h, 0x000000FF); // black
			w++;
		}
		h++;
	}
}

void	draw_mandelbrot(t_specs *specs)
{
	double		w;
	double		h;
	t_complex	c_plane; //complex plane
	int			iterations;

	h = 0;
	while (h < 800)
	{
		w = 0;
		while (w < 800)
		{
			c_plane = pixel_to_complex(w, h);
			iterations = calc_infinity_mandelbrot(c_plane);
			if (iterations > 0)
				mlx_put_pixel(specs->img, w, h, color_progression(iterations));
			else
				mlx_put_pixel(specs->img, w, h, 0x000000FF); // black
			w++;
		}
		h++;
	}
}

uint32_t	color_progression(int iterations)
{
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;
	uint32_t	alpha;
	uint32_t	hex_value;

	alpha = 255;
	if (iterations < (0.25 * MAX_ITERATIONS))
	{
		red = 230 - (iterations / (.25 * MAX_ITERATIONS)) * 230;
		green = 0;
		blue = 230;
	}
	if (iterations >= (0.25 * MAX_ITERATIONS) && iterations < (0.5 * MAX_ITERATIONS))
	{
		red = 0;
		green = 0 + (iterations / MAX_ITERATIONS) / (.25 * MAX_ITERATIONS) * 230;
		blue = 230;
	}
	if (iterations >= (0.5 * MAX_ITERATIONS) && iterations < (0.75 * MAX_ITERATIONS))
	{
		red = 0;
		green = 230;
		blue = 230 - (iterations / MAX_ITERATIONS) / (.25 * MAX_ITERATIONS) * 230;
	}
	if (iterations >= (0.75 * MAX_ITERATIONS))
	{
		red = 0 + (iterations / MAX_ITERATIONS) / (.25 * MAX_ITERATIONS) * 230;
		green = 230;
		blue = 0;
	}
	hex_value = (red << 24) | (green << 16) | (blue << 8) | alpha;
	return (hex_value);
}

int	check_params(int argc, char *argv[], t_specs *specs)
{
	if (argc > 1 && ft_strncmp(argv[1], "Mandelbrot", 11) == 0 && argc < 3)
	{
		specs->fractol = argv[1];
		specs->draw = draw_mandelbrot;
		return (1);
	}
	if (argc == 4 && ft_strncmp(argv[1], "Julia", 6) == 0)
	{
		specs->fractol = argv[1];
		specs->julia_rc = ft_atof((const char *)argv[2]);
		specs->julia_ic = ft_atof((const char *)argv[3]);
		if (specs->julia_rc >= -1 && specs->julia_rc <= 1
			&& specs->julia_ic >= -1 && specs->julia_ic <= 1)
		{
			specs->draw = draw_julia;
			return (1);
		}
	}
	ft_printf("Enter 'Julia' and two numbers between -1 and 1 or enter 'Mandelbrot'");
	return (0);
}
