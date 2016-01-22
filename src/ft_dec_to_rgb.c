/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dec_to_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/23 21:53:28 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/05/30 13:22:13 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_color	*ft_dec_to_rgb(int c)
{
	t_color	*color;

	color = (t_color*)malloc(sizeof(t_color));
	color->red = (c >> 16) & 0xff;
	color->green = (c >> 8) & 0xff;
	color->blue = c & 0xff;
	return (color);
}
