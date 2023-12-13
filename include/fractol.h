/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <jvets@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:02:22 by jvets             #+#    #+#             */
/*   Updated: 2023/12/13 19:06:37 by jvets            ###   ########.fr       */
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

typedef struct s_complex_number
{
	double	r;
	double	i;
}	t_complex;

typedef struct s_specifications
{
	char		*fractol;
	double		julia_rc;
	double		julia_ic;
	mlx_t		*mlx;
	mlx_image_t	*img;
	void		(*draw)(struct s_specifications *specs);
	double		w_offset; //b in my pixel to complex plain formula
	double		h_offset;
}	t_specs;

typedef struct s_calc
{
	double	rz;
	double	iz;
	double	magnitude;
	int		i; // i = iterations
	double	rz_product;
	double	iz_product;
}	t_calc;

t_complex	pixel_to_complex(double w, double h, t_specs **specs);
int			calculate_infinity(t_complex c_plane, t_specs **specs);
uint32_t	color_progression(int iterations);
void		draw_julia(t_specs *specs);
static void	convert_numbers(const char *nptr, double *result);
double		ft_atof(const char *nptr);
int			calc_infinity_mandelbrot(t_complex c_plane);
void		draw_mandelbrot(t_specs *specs);
int			check_params(int argc, char *argv[], t_specs *specs);
static void ft_error(void);
void		esc(mlx_key_data_t keydata, void *param);
void		select_draw(void *param);

#endif

