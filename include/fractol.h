/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <jvets@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:02:22 by jvets             #+#    #+#             */
/*   Updated: 2023/11/22 18:44:46 by jvets            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include "../printf/includes/ft_printf.h"

// typedef struct mlx
// {
// 	void	*window;
// 	void	*context;
// 	int32_t	width;
// 	int32_t	height;
// 	double	delta_time;
// }	mlx_t;

typedef struct s_complex_number
{
	double	r;
	double	i;
}	t_inum;

t_inum	pixel_to_complex(double w, double h);
int	calculate_infinity(t_inum c_plane, double rc, double ic);
uint32_t	color_progression(int iterations);
void	draw_julia(mlx_image_t *img, int julia_1, int julia_2);

#endif

