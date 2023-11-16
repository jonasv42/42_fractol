/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <jvets@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:27:28 by jvets             #+#    #+#             */
/*   Updated: 2023/11/15 23:28:35 by jvets            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../printf/includes/ft_printf.h"
#include "../libft/libft.h"
#include <math.h>
#define WIDTH 256
#define HEIGHT 256
#define BPP sizeof(int32_t)

int	check_params(int argc, char *argv[], int *julia_1, int *julia_2);
static void ft_error(void);
void	esc(mlx_key_data_t keydata, void *param);
void	draw(mlx_image_t *img);
int	calculate_infinity(int x, int y, double rc, double ic);

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

	img = mlx_new_image(mlx, 800, 600);
	ft_memset(img->pixels, 255, img->width * img->height * BPP);
	
	mlx_image_to_window(mlx, img, 0, 0);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_printf("Error");
	draw(img);

	mlx_key_hook(mlx, &esc, &mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

void	draw(mlx_image_t *img)
{
	double rc = -0.8;
	double ic = 0.156;

	int x;
	int y;

	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			calculate_infinity(x, y, rc, ic);
			x++;
		}
		y++;
	}
	mlx_put_pixel(img, 100, 100, 0xFF0000);
	mlx_put_pixel(img, 10, 10, 0xFF0000);
	mlx_put_pixel(img, 0, 0, 0xFF0000);
}

int	calculate_infinity(int x, int y, double rc, double ic)
{
	double	rz;
	double	iz;
	double	square;
	double	magnitude;
	double	i;

		rz = (x - 399);
		iz = (y + 299);

	while (i < 1000) // z = z * z + c
	{
		rz_product = (rz * rz) - (iz * iz);
		iz_product = (rz * iz) + (iz * rz);
		rz = rz_product + rc;
		iz = iz_product + ic;
		i++
		magnitude = hypot(rz, iz);
		if (magnitude > 100)
			return (i);
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
