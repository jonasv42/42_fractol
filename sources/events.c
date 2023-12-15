/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <jvets@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:51:00 by jvets             #+#    #+#             */
/*   Updated: 2023/12/14 23:31:41 by jvets            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	esc(mlx_key_data_t keydata, void *param)
{
	t_specs	*specs;

	specs = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(specs->mlx); //exit (0); ?
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		ft_shift_img(1, 0, -1, specs);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		ft_shift_img(1, 0, 1, specs);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		ft_shift_img(0, 1, 1, specs);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		ft_shift_img(0, 1, -1, specs);
	if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS)
		ft_zoom(1, specs);
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
		ft_zoom(-1, specs);
	if (keydata.key == MLX_KEY_KP_ADD && keydata.action == MLX_PRESS)
		specs->max_iterations += 10;
	if (keydata.key == MLX_KEY_KP_SUBTRACT && keydata.action == MLX_PRESS)
		specs->max_iterations -= 10;
}

void	ft_shift_img(int x, int y, int sign, t_specs *specs)
{
	if (x == 1 && sign < 0)
	{
		specs->x0 -= 0.05 * specs->scale_x;
		specs->x800 -= 0.05 * specs->scale_x;
	}
	if (x == 1 && sign > 0)
	{
		specs->x0 += 0.05 * specs->scale_x;
		specs->x800 += 0.05 * specs->scale_x;
	}
	if (y == 1 && sign > 0)
	{
		specs->y0 += 0.05 * specs->scale_x;
		specs->y800 += 0.05 * specs->scale_x;
	}
	if (y == 1 && sign < 0)
	{
		specs->y0 -= 0.05 * specs->scale_x;
		specs->y800 -= 0.05 * specs->scale_x;
	}
}

void	ft_zoom(double sign, t_specs *specs)
{
	double	aux;

	aux = 0.05 * fabs(specs->x0 - specs->x800) * sign; // calculate distance x0 & x800
	specs->x0 += aux;
	specs->x800 -= aux;
	specs->y0 -= aux;
	specs->y800 += aux;
	specs->scale_x = ((specs->x800) + (-1 * (specs->x0)));
	specs->scale_y = ((specs->y800) + (-1 * (specs->y0)));
	if (sign > 0 || specs->max_iterations > 25) // prevent too low a quality
		specs->max_iterations += sign;
}

void	ft_scroll(double xdelta, double ydelta, void *param)
{
	t_specs	*specs;
	int32_t	width;
	int32_t	height;

	specs = param;
	if (ydelta < 0) // zoom in
		ft_zoom(1, specs);
	if (ydelta > 0)
		ft_zoom (-1, specs);
}
