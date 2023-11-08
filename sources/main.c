/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <jvets@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:27:28 by jvets             #+#    #+#             */
/*   Updated: 2023/11/08 20:06:39 by jvets            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <string.h> // remove and use libft
#include <stdlib.h>

int	check_params(int argc, char *argv[], int *julia_1, int *julia_2);

int	main(int argc, char *argv[])
{
	int	julia_1;
	int	julia_2;

	if (!check_params(argc, argv, &julia_1, &julia_2))
	{
		printf("Enter 'Julia' and a number between -1 and 1 or 'Mandelbrot'"); // replace with ft_printf
		return (0);
	}
	return (0);
}

int	check_params(int argc, char *argv[], int *julia_1, int *julia_2)
{
	if (argc > 1 && strcmp(argv[1], "Mandelbrot") == 0 && argc < 3)
		return (1);
	if (argc == 4 && strcmp(argv[1], "Julia") == 0)
	{
		*julia_1 = atoi(argv[2]); // replace with ft_atoi
		*julia_2 = atoi(argv[3]); // replace with ft_atoi
		if (*julia_1 > -1 && *julia_1 < 1 && *julia_2 > -1 && *julia_2 < 1)
			return (1);
	}
	return (0);
}
