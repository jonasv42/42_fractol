/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <jvets@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:27:28 by jvets             #+#    #+#             */
/*   Updated: 2023/12/15 19:21:45 by jvets            ###   ########.fr       */
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
	if (iterations < (0.25 * (*specs)->max_iterations))
	{
		(*specs)->red = 230 - (iterations / (.25 * (*specs)->max_iterations)) * 230;
		(*specs)->green = 0;
		(*specs)->blue = 230;
	}
	if (iterations >= (0.25 * (*specs)->max_iterations) && iterations < (0.5 * (*specs)->max_iterations))
	{
		(*specs)->red = 0;
		(*specs)->green = 0 + (iterations / (*specs)->max_iterations) / (.25 * (*specs)->max_iterations) * 230;
		(*specs)->blue = 230;
	}
	if (iterations >= (0.5 * (*specs)->max_iterations) && iterations < (0.75 * (*specs)->max_iterations))
	{
		(*specs)->red = 0;
		(*specs)->green = 230;
		(*specs)->blue = 230 - (iterations / (*specs)->max_iterations) / (.25 * (*specs)->max_iterations) * 230;
	}
	if (iterations >= (0.75 * (*specs)->max_iterations))
	{
		(*specs)->red = 0 + (iterations / (*specs)->max_iterations) / (.25 * (*specs)->max_iterations) * 230;
		(*specs)->green = 230;
		(*specs)->blue = 0;
	}
	(*specs)->hex_value = ((*specs)->red << 24) | ((*specs)->green << 16) | ((*specs)->blue << 8) | 255;
	return ((*specs)->hex_value);
}

int	check_params(int argc, char *argv[], t_specs *specs)
{
	if (argc > 1 && ft_strncmp(argv[1], "Mandelbrot", 11) == 0 && argc < 3)
	{
		specs->draw = draw_mandelbrot;
		return (1);
	}
	if (argc == 4 && ft_strncmp(argv[1], "Julia", 6) == 0 && ft_isnum(argv[2]) && ft_isnum(argv[3]))
	{
		specs->julia_rc = ft_atof((const char *)argv[2]);
		specs->julia_ic = ft_atof((const char *)argv[3]);
		if (specs->julia_rc >= -2 && specs->julia_rc <= 2
			&& specs->julia_ic >= -2 && specs->julia_ic <= 2)
		{
			specs->draw = draw_julia;
			return (1);
		}
	}
	ft_printf("Enter 'Julia' and two numbers between -2 and 2\n");
	ft_printf("or enter 'Mandelbrot'\n");
	return (0);
}

int	ft_isnum(const char *str)
{
	if ((*str) == '-')
		str++;
	while (*str)
	{
		if ((!ft_isdigit(*str) && (*str) != '.') || 
		((*str) == '.' && !(ft_isdigit(*(str + 1)))))
			return (0);
		str++;
	}
	return (1);
}
