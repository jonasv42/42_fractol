/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <jvets@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:31:10 by jvets             #+#    #+#             */
/*   Updated: 2023/12/12 18:38:04 by jvets            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

t_inum	pixel_to_complex(double w, double h)
{
	t_inum		result;
	static int	i;

	i = 0;
	result.r = (4.0 / 800) * w - 2.0;
	result.i = -1.0 * (4.0 / 800) * h + 2.0;
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
	}
	return (0);
}

int	calc_infinity_mandelbrot(t_inum c_plane)
{
	double	rz;
	double	iz;
	double	square;
	double	magnitude;
	int		i; // i = iterations
	double	rz_product;
	double	iz_product;

	i = 1;
	rz = 0.0;
	iz = 0.0;
	while (i < MAX_ITERATIONS) // z = z * z + c
	{
		rz_product = (rz * rz) - (iz * iz);
		iz_product = (rz * iz) + (iz * rz);
		rz = rz_product + c_plane.r;
		iz = iz_product + c_plane.i;
		magnitude = hypot(rz, iz);
		if (magnitude > 1.5)
			return (i);
		i++;
	}
	return (0);
}

double	ft_atof(const char *nptr)
{
	double	sign;
	double	result;

	sign = 1;
	result = 0;
	while (*nptr)
	{
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
			return (result * sign);
		}
	}
	return (0);
}

static void	convert_numbers(const char *nptr, double *result)
{
	int	dot;

	dot = -1;
	while ((*nptr >= '0' && *nptr <= '9') || *nptr == '.')
	{
		if (*nptr == '.')
			dot++;
		else
			*result = (*result * 10) + (*nptr - '0');
		if ((dot > -1 && *nptr != '.'))
			dot++;
		nptr++;
	}
	if (dot > -1)
		*result = *result / pow(10, dot);
}
