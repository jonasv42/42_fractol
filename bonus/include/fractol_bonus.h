/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <jvets@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:02:22 by jvets             #+#    #+#             */
/*   Updated: 2023/12/15 20:34:59 by jvets            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIDTH 800
# define HEIGHT 800
# define MAX_ITERATIONS 100

# include <stdint.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../printf/includes/ft_printf.h"

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
	double		scale_y;
	double		scale_x;
	int			max_iterations;
	double		x0;
	double		x800;
	double		y0;
	double		y800;
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;
	uint32_t	hex_value;
}	t_specs;

typedef struct s_calc
{
	double	rz;
	double	iz;
	double	magnitude;
	int		i;
	double	rz_product;
	double	iz_product;
}	t_calc;

t_complex	pixel_to_complex(double w, double h, t_specs **specs);
int			calculate_infinity(t_complex c_plane, t_specs **specs);
uint32_t	ft_color(int iterations, t_specs **specs);
void		draw_julia(t_specs *specs);
void		convert_numbers(const char *nptr, double *result);
double		ft_atof(const char *nptr);
int			calc_infinity_mandelbrot(t_complex c_plane, t_specs **specs);
void		draw_mandelbrot(t_specs *specs);
int			check_params(int argc, char *argv[], t_specs *specs);
void		esc(mlx_key_data_t keydata, void *param);
void		select_draw(void *param);
void		ft_zoom(double zoomfactor, t_specs *specs);
void		ft_shift_img(int x, int y, int sign, t_specs *specs);
void		ft_scroll(double xdelta, double ydelta, void *param);
void		ft_init(char *argv[], t_specs *specs);
int			ft_isnum(const char *str);

#endif
