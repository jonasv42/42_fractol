/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <jvets@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:27:28 by jvets             #+#    #+#             */
/*   Updated: 2023/11/22 19:03:53 by jvets            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

#define WIDTH 256
#define HEIGHT 256
#define BPP sizeof(int32_t)
#define MAX_ITERATIONS 100

int			check_params(int argc, char *argv[], int *julia_1, int *julia_2);
static void ft_error(void);
void		esc(mlx_key_data_t keydata, void *param);

int	main(int argc, char *argv[])
{
	int	julia_1;
	int	julia_2;
	mlx_t	*mlx;
	mlx_image_t	*img;

	julia_1 = 0;
	julia_2 = 0;
	if (!check_params(argc, argv, &julia_1, &julia_2))
	{
		ft_printf("Enter 'Julia' and two numbers between -1 and 1 or enter 'Mandelbrot'");
		return (0);
	}
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx = mlx_init(WIDTH, HEIGHT, "fractal", true);
	if (!mlx)
		ft_printf("Error");

	img = mlx_new_image(mlx, 800, 800);
	ft_memset(img->pixels, 255, img->width * img->height * BPP);
	
	mlx_image_to_window(mlx, img, 0, 0);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_printf("Error");
	draw_julia(img, julia_1, julia_2);

	mlx_key_hook(mlx, &esc, &mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

void	draw_julia(mlx_image_t *img, int julia_1, int julia_2)
{
	double rc = (double)julia_1;
	double ic = (double)julia_2;
	// double rc = -0.8;
	// double ic = 0.156;
	// double rc = -0.5;
	// double ic = 0.5;
	// double rc = 0.3400000000000004;
	// double ic = -0.08000000000000018;
	// double rc = 0.54;
	// double ic = -0.5;

	double w;
	double h;
	t_inum	c_plane; //complex plane

	int		iterations;

	// yellow = 4242671103; // FCE205FF in hexa

	h = 0;
	while (h < 800)
	{
		w = 0;
		while (w < 800)
		{
			c_plane = pixel_to_complex(w, h);
			iterations = calculate_infinity(c_plane, rc, ic);
			if (iterations > 0)
				mlx_put_pixel(img, w, h, color_progression(iterations));
			else
				mlx_put_pixel(img, w, h, 0x000000FF); // black
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
		red = 230 - (iterations/(.25*MAX_ITERATIONS)) * 230;
		green = 0;
		blue = 230;
	}
	if (iterations >= (0.25 * MAX_ITERATIONS) && iterations < (0.5 * MAX_ITERATIONS))
	{
		red = 0;
		green = 0 + (iterations/MAX_ITERATIONS)/(.25*MAX_ITERATIONS) * 230;
		blue = 230;
	}
	if (iterations >= (0.5 * MAX_ITERATIONS) && iterations < (0.75 * MAX_ITERATIONS))
	{
		red = 0;
		green = 230;
		blue = 230 - (iterations/MAX_ITERATIONS)/(.25*MAX_ITERATIONS) * 230;
	}
	if (iterations >= (0.75 * MAX_ITERATIONS))
	{
		red = 0 + (iterations/MAX_ITERATIONS)/(.25*MAX_ITERATIONS) * 230;
		green = 230;
		blue = 0;
	}
	hex_value = (red << 24) | (green << 16) | (blue << 8) | alpha;
	return (hex_value);
}

t_inum	pixel_to_complex(double w, double h)
{
	t_inum	result;
	static int i = 0;

	result.r = (4.0 / 800) * w - 2.0;
	result.i = -1.0 * (4.0 / 800) * h + 2.0;
	// if (i == 0)
	// {
	// 	printf("width %f, height %f\nwordt\nreal %f, imag. %f", w, h, result.r, result.i);
	// 	i++;
	// }
	return (result);
}

int	calculate_infinity(t_inum c_plane, double rc, double ic)
{
	double	rz;
	double	iz;
	double	square;
	double	magnitude;
	int		i; // i = iterations
	double	rz_product;
	double	iz_product;

	i = 1;

	while (i < MAX_ITERATIONS) // z = z * z + c
	{
		rz_product = (c_plane.r * c_plane.r) - (c_plane.i * c_plane.i);
		iz_product = (c_plane.r * c_plane.i) + (c_plane.i * c_plane.r);
		c_plane.r = rz_product + rc;
		c_plane.i = iz_product + ic;
		magnitude = hypot(c_plane.r, c_plane.i);
		if (magnitude > 1.5)
			return (i);
		i++;
		// if (i == 10)
		// 	printf("magnitude %f", magnitude);
	}
	return (0);
}

void	esc(mlx_key_data_t keydata, void *mlx)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window((mlx_t *)mlx);
		//exit (0);
	}
}

int	check_params(int argc, char *argv[], int *julia_1, int *julia_2)
{
	if (argc > 1 && ft_strncmp(argv[1], "Mandelbrot", 11) == 0 && argc < 3)
		return (1);
	if (argc == 4 && ft_strncmp(argv[1], "Julia", 6) == 0)
	{
		*julia_1 = ft_atoi(argv[2]);
		*julia_2 = ft_atoi(argv[3]);
		if (*julia_1 > -1 && *julia_1 < 1 && *julia_2 > -1 && *julia_2 < 1)
			return (1);
	}
	return (0);
}

double	atof(const char *nptr)
{
	double	sign;
	double	result;

	if (*nptr == ' ' || (*nptr > 8 && *nptr < 14))
		nptr++;
	else if (*nptr == '-' || *nptr == '+')
	{
		if (nptr[1] < '0' || nptr[1] > '9')
			return (0);
		if (*nptr == '-')
			sign = -1.0;
		nptr++;
	}
	else
	{
		convert_numbers(nptr, &result);
		//tratar . -> pular o ponto, gravar quantos caráteres tem após isso e dividir por 10^1, 10^2, 10^3, etc.
		return (result * sign);
	}
	return (result);	
}

static void	convert_numbers(const char *nptr, double *result)
{
	while (*nptr >= '0' && *nptr <= '9')
	{
		*result = (*result * 10) + (*nptr - '0');
		nptr++;
	}
}