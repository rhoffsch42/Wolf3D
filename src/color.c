/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 07:35:53 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/06/04 08:30:55 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		smallest(char x, char y)
{
	char	min;

	if (x <= y)
		min = x;
	else
		min = y;
	return (min);
}

int		hightest(char x, char y)
{
	char	max;

	if (x >= y)
		max = x;
	else
		max = y;
	return (max);
}

void	ft_color_satur(char *red, char *green, char *blue, double ratio)
{
	int	min;
	int	max;

	min = (int)smallest(*red, smallest(*green, *blue));
	max = (int)hightest(*red, hightest(*green, *blue));
	min = (min + max) / 2;
	*red += (char)((1.0 - ratio) * (float)(min - *red));
	*green += (char)((1.0 - ratio) * (float)(min - *green));
	*blue += (char)((1.0 - ratio) * (float)(min - *blue));
}

void	color_satur(char *red, char *green, char *blue, double ratio)
{
	double	p;
	double	r;
	double	g;
	double	b;

	r = (double)*red;
	g = (double)*green;
	b = (double)*blue;
	p = sqrt(r * r * 0.299 + g * g * 0.587 + b * b * 0.114);
	*red = (char)(p + (r - p) * ratio);
	*green = (char)(p + (g - p) * ratio);
	*blue = (char)(p + (b - p) * ratio);
}
