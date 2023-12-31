/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <jvets@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:23:42 by jvets             #+#    #+#             */
/*   Updated: 2023/12/15 19:26:43 by jvets            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	select_draw(void *param)
{
	t_specs	*specs;

	specs = param;
	specs->draw(specs);
}

void	draw_julia(t_specs *specs)
{
	int			iterations;
	double		w;
	double		h;
	t_complex	c_plane;

	h = 0;
	while (h < 800)
	{
		w = 0;
		while (w < 800)
		{
			c_plane = pixel_to_complex(w, h, &specs);
			iterations = calculate_infinity(c_plane, &specs);
			if (iterations > 0)
				mlx_put_pixel(specs->img, w, h, ft_color(iterations, &specs));
			else
				mlx_put_pixel(specs->img, w, h, 0x000000FF);
			w++;
		}
		h++;
	}
}

void	draw_mandelbrot(t_specs *specs)
{
	int			iterations;
	double		w;
	double		h;
	t_complex	c_plane;

	h = 0;
	while (h < 800)
	{
		w = 0;
		while (w < 800)
		{
			c_plane = pixel_to_complex(w, h, &specs);
			iterations = calc_infinity_mandelbrot(c_plane, &specs);
			if (iterations > 0)
				mlx_put_pixel(specs->img, w, h, ft_color(iterations, &specs));
			else
				mlx_put_pixel(specs->img, w, h, 0x000000FF);
			w++;
		}
		h++;
	}
}
