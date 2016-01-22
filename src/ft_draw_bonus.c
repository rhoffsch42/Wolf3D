/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/23 17:00:15 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/05/31 21:10:33 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_draw_crosshair(t_env *e)
{
	int	x;
	int	y;
	int	i;

	x = e->win_x / 2;
	y = e->win_y / 2;
	i = 6;
	ft_mlx_image_pixel_put(*e, x, y, 0x000000);
	ft_mlx_image_pixel_put(*e, x - 1, y - 1, 0xFFFFFF);
	while (i >= 3)
	{
		ft_mlx_image_pixel_put(*e, x + i, y, 0x000000);
		ft_mlx_image_pixel_put(*e, x, y + i, 0x000000);
		ft_mlx_image_pixel_put(*e, x - i, y, 0x000000);
		ft_mlx_image_pixel_put(*e, x, y - i, 0x000000);
		ft_mlx_image_pixel_put(*e, x + i - 1, y - 1, 0xFFFFFF);
		ft_mlx_image_pixel_put(*e, x - 1, y + i - 1, 0xFFFFFF);
		ft_mlx_image_pixel_put(*e, x - i - 1, y - 1, 0xFFFFFF);
		ft_mlx_image_pixel_put(*e, x - 1, y - i - 1, 0xFFFFFF);
		i--;
	}
}

static void	ft_draw_outscope(t_env *e, int y)
{
	int		x;
	float	ab;
	float	bc;
	float	ac;

	bc = ((float)e->win_x * 3.0) / 8.0;
	bc = bc * bc;
	ab = fabs((float)(e->win_y / 2 - y));
	ab = ab * ab;
	ac = sqrt(bc - ab);
	x = 0;
	while (x < e->win_x)
	{
		if (x < e->win_x / 2 - ac || x > e->win_x / 2 + ac)
			ft_mlx_image_pixel_put(*e, x, y, 0x000000);
		x++;
	}
}

void		ft_draw_scope(t_env *e)
{
	int		x;
	int		y;

	y = e->win_y / 2;
	x = 0;
	while (x < e->win_x)
	{
		if (x < e->win_x / 2 - 10 || x > e->win_x / 2 + 10 \
			|| x == e->win_x / 2)
			ft_mlx_image_pixel_put(*e, x, y, 0x000000);
		x++;
	}
	y = 0;
	x = e->win_x / 2;
	while (y < e->win_y)
	{
		if (y < e->win_y / 2 - 10 || y > e->win_y / 2 + 10)
			ft_mlx_image_pixel_put(*e, x, y, 0x000000);
		ft_draw_outscope(e, y);
		y++;
	}
}

void		ft_draw_cam(t_env *e)
{
	int	x;
	int	y;
	int	color;

	color = 0x000000;
	x = e->cam_x;
	y = e->cam_y;
	ft_mlx_image_pixel_put(*e, x, y, color);
	ft_mlx_image_pixel_put(*e, x + 1, y, color);
	ft_mlx_image_pixel_put(*e, x, y + 1, color);
	ft_mlx_image_pixel_put(*e, x + 1, y + 1, color);
	ft_mlx_image_pixel_put(*e, x - 1, y, color);
	ft_mlx_image_pixel_put(*e, x - 1, y - 1, color);
	ft_mlx_image_pixel_put(*e, x - 1, y + 1, color);
	ft_mlx_image_pixel_put(*e, x, y - 1, color);
	ft_mlx_image_pixel_put(*e, x + 1, y - 1, color);
}

void		ft_draw_gun(t_env *e, int y, int diffx, int diffy)
{
	t_im	src;
	t_im	dst;
	int		tmp1;
	int		tmp2;
	int		x;

	src.px = mlx_get_data_addr(e->xpm[1], &src.bpp, &src.sizeline, &src.endian);
	dst.px = mlx_get_data_addr(e->img, &dst.bpp, &dst.sizeline, &dst.endian);
	while (y < 190)
	{
		x = 0;
		while (x < 280)
		{
			tmp1 = y * src.sizeline + (src.bpp / 8) * x;
			if (src.px[tmp1 + 3] != -1)
			{
				tmp2 = (y + diffy) * dst.sizeline + (dst.bpp / 8) * (x + diffx);
				dst.px[tmp2] = src.px[tmp1];
				dst.px[tmp2 + 1] = src.px[tmp1 + 1];
				dst.px[tmp2 + 2] = src.px[tmp1 + 2];
			}
			x++;
		}
		y++;
	}
}
