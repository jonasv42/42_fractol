/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvets <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:02:22 by jvets             #+#    #+#             */
/*   Updated: 2023/11/10 21:09:19 by jvets            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdint.h>

typedef struct mlx
{
	void	*window;
	void	*context;
	int32_t	width;
	int32_t	height;
	double	delta_time;
}	mlx_t;

#endif
