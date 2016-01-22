/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_image_put_pixel.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 15:57:20 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/05/30 13:21:13 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_mlx_image_pixel_put(t_env e, int x, int y, int color)
{
	char			*pixel;
	int				bpp;
	int				sizeline;
	int				endian;
	unsigned int	new_color;

	if (x >= e.win_x || y >= e.win_y || y < 0 || x < 0)
		return (0);
	new_color = mlx_get_color_value(e.mlx, color);
	pixel = mlx_get_data_addr(e.img, &bpp, &sizeline, &endian);
	pixel[y * sizeline + (bpp / 8) * x] = (new_color & 0xFF);
	pixel[y * sizeline + (bpp / 8) * x + 1] = (new_color & 0xFF00) >> 8;
	pixel[y * sizeline + (bpp / 8) * x + 2] = (new_color & 0xFF0000) >> 16;
	return (0);
}
