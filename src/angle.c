/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/18 16:20:44 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/06/04 07:36:16 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

float	rtod(float radians)
{
	return (radians * (180.0 / M_PI));
}

float	dtor(float degree)
{
	return (degree * M_PI / 180.0);
}

float	ft_fmodulo(float n, float mod)
{
	while (n >= mod)
		n -= mod;
	return (n);
}

float	ft_degree_scale(float degree)
{
	if (degree > 0.0)
		degree = ft_fmodulo(degree, 360.0);
	else if (degree < 0.0)
	{
		while (degree <= -360.0)
			degree += 360.0;
		if (degree < 0.0)
			degree = 360.00000 + degree;
	}
	return (degree);
}

int		co(int val, float coef)
{
	if (val < 0)
		val += 255;
	return ((int)((float)val * coef));
}
