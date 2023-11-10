/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <jvets@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:27:28 by jvets             #+#    #+#             */
/*   Updated: 2023/11/09 21:19:53 by jvets            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../printf/includes/ft_printf.h"
#include "../libft/libft.h"

int	check_params(int argc, char *argv[], int *julia_1, int *julia_2);

int	main(int argc, char *argv[])
{
	int	julia_1;
	int	julia_2;

	if (!check_params(argc, argv, &julia_1, &julia_2))
	{
		ft_printf("Enter 'Julia' and two numbers between -1 and 1 or enter 'Mandelbrot'");
		return (0);
	}
	return (0);
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
