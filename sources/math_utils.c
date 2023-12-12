/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <jvets@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:31:10 by jvets             #+#    #+#             */
/*   Updated: 2023/12/12 19:10:28 by jvets            ###   ########.fr       */
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

int	calculate_infinity(t_inum c_plane, t_specs **specs)
{
	t_calc	calc;

	calc.i = 1;
	while (calc.i < MAX_ITERATIONS) // z = z * z + c
	{
		calc.rz_product = (c_plane.r * c_plane.r) - (c_plane.i * c_plane.i);
		calc.iz_product = (c_plane.r * c_plane.i) + (c_plane.i * c_plane.r);
		c_plane.r = calc.rz_product + (*specs)->julia_rc;
		c_plane.i = calc.iz_product + (*specs)->julia_ic;
		calc.magnitude = hypot(c_plane.r, c_plane.i);
		if (calc.magnitude > 1.5)
			return (calc.i);
		calc.i++;
	}
	return (0);
}

int	calc_infinity_mandelbrot(t_inum c_plane)
{
	t_calc	calc;

	calc.i = 1;
	calc.rz = 0.0;
	calc.iz = 0.0;
	while (calc.i < MAX_ITERATIONS) // z = z * z + c
	{
		calc.rz_product = (calc.rz * calc.rz) - (calc.iz * calc.iz);
		calc.iz_product = (calc.rz * calc.iz) + (calc.iz * calc.rz);
		calc.rz = calc.rz_product + c_plane.r;
		calc.iz = calc.iz_product + c_plane.i;
		calc.magnitude = hypot(calc.rz, calc.iz);
		if (calc.magnitude > 1.5)
			return (calc.i);
		calc.i++;
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
