/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <jvets@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:02:22 by jvets             #+#    #+#             */
/*   Updated: 2023/12/11 22:55:04 by jvets            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include "../printf/includes/ft_printf.h"

#define WIDTH 800
#define HEIGHT 800
#define BPP sizeof(int32_t)
#define MAX_ITERATIONS 300

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

typedef struct s_specifications
{
	char	*fractol;
	double	julia_1;
	double	julia_2;
}	t_specs;

t_inum	pixel_to_complex(double w, double h);
int	calculate_infinity(t_inum c_plane, double rc, double ic);
uint32_t	color_progression(int iterations);
void	draw_julia(mlx_image_t *img, t_specs *specs);
static void	convert_numbers(const char *nptr, double *result);
double	ft_atof(const char *nptr);
int	calc_infinity_mandelbrot(t_inum c_plane);
void	draw_mandelbrot(mlx_image_t *img, t_specs *specs);

#endif

