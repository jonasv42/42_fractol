/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <jvets@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:51:00 by jvets             #+#    #+#             */
/*   Updated: 2023/12/13 23:13:24 by jvets            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	esc(mlx_key_data_t keydata, void *param)
{
	t_specs	*specs;

	specs = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(specs->mlx);
		//exit (0);
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		specs->w_offset += 0.025 * specs->scale;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		specs->w_offset -= 0.025 * specs->scale;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		specs->h_offset += 0.025 * specs->scale;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		specs->h_offset -= 0.025 * specs->scale;
	if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS)
	{
		specs->scale = (specs->scale) * 0.95;
		specs->max_iterations += 1;
	}
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
	{
		specs->scale = (specs->scale) * 1.05;
		specs->max_iterations -= 1;
	}
}
