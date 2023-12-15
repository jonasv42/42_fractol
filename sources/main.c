/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <jvets@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:27:28 by jvets             #+#    #+#             */
/*   Updated: 2023/12/14 22:30:02 by jvets            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	main(int argc, char *argv[])
{
	t_specs	specs;

	if (!check_params(argc, argv, &specs))
		return (EXIT_FAILURE);
	ft_init(argv, &specs);
	specs.mlx = mlx_init(WIDTH, HEIGHT, specs.fractol, true);
	if (!specs.mlx)
		return (EXIT_FAILURE);
	specs.img = mlx_new_image(specs.mlx, WIDTH, HEIGHT);
	if (!specs.img)
		return (EXIT_FAILURE);
	mlx_loop_hook(specs.mlx, &select_draw, &specs);
	if (!specs.img || (mlx_image_to_window(specs.mlx, specs.img, 0, 0) < 0))
		ft_printf("Error");
	mlx_key_hook(specs.mlx, &esc, &specs);
	mlx_scroll_hook(specs.mlx, &ft_scroll, &specs);
	mlx_loop(specs.mlx);
	mlx_terminate(specs.mlx);
	return (0);
}

void	ft_init(char *argv[], t_specs *specs)
{
	(*specs).fractol = argv[1];
	(*specs).scale_x = 4;
	(*specs).scale_y = -4;
	(*specs).max_iterations = 25;
	(*specs).x0 = -2;
	(*specs).x800 = 2;
	(*specs).y0 = 2;
	(*specs).y800 = -2;
}

uint32_t	ft_color(int iterations, t_specs **specs)
{
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;
	uint32_t	alpha;
	uint32_t	hex_value;

	alpha = 255;
	if (iterations < (0.25 * (*specs)->max_iterations))
	{
		red = 230 - (iterations / (.25 * (*specs)->max_iterations)) * 230;
		green = 0;
		blue = 230;
	}
	if (iterations >= (0.25 * (*specs)->max_iterations) && iterations < (0.5 * (*specs)->max_iterations))
	{
		red = 0;
		green = 0 + (iterations / (*specs)->max_iterations) / (.25 * (*specs)->max_iterations) * 230;
		blue = 230;
	}
	if (iterations >= (0.5 * (*specs)->max_iterations) && iterations < (0.75 * (*specs)->max_iterations))
	{
		red = 0;
		green = 230;
		blue = 230 - (iterations / (*specs)->max_iterations) / (.25 * (*specs)->max_iterations) * 230;
	}
	if (iterations >= (0.75 * (*specs)->max_iterations))
	{
		red = 0 + (iterations / (*specs)->max_iterations) / (.25 * (*specs)->max_iterations) * 230;
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
		specs->draw = draw_mandelbrot;
		return (1);
	}
	if (argc == 4 && ft_strncmp(argv[1], "Julia", 6) == 0)
	{
		specs->julia_rc = ft_atof((const char *)argv[2]);
		specs->julia_ic = ft_atof((const char *)argv[3]);
		if (specs->julia_rc >= -1 && specs->julia_rc <= 1
			&& specs->julia_ic >= -1 && specs->julia_ic <= 1)
		{
			specs->draw = draw_julia;
			return (1);
		}
	}
	ft_printf("Enter 'Julia' and two numbers between -1 and 1\n");
	ft_printf("or enter 'Mandelbrot'\n");
	return (0);
}
