/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_bonus2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 00:46:13 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/06/04 08:46:17 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_draw_bg(t_env *e, int x, int y)
{
	t_im	im1;
	t_im	im2;
	int		tmp1;
	int		tmp2;
	int		tmp3;

	im1.px = mlx_get_data_addr(e->xpm[0], &im1.bpp, &im1.sizeline, &im1.endian);
	im2.px = mlx_get_data_addr(e->img, &im2.bpp, &im2.sizeline, &im2.endian);
	tmp3 = (int)((e->cam_mid / 360.0) * (e->zoom == 0 ? SKY : SKY * 2.0));
	while (y < 300)
	{
		x = 0;
		while (x < e->win_x)
		{
			tmp1 = y * im1.sizeline + (im1.bpp / 8) * (x - tmp3);
			tmp2 = y * im2.sizeline + (im2.bpp / 8) * x;
			im2.px[tmp2 + 0] = co(im1.px[tmp1 + 0], e->shad_coef);
			im2.px[tmp2 + 1] = co(im1.px[tmp1 + 1], e->shad_coef);
			im2.px[tmp2 + 2] = co(im1.px[tmp1 + 2], e->shad_coef);
			x++;
		}
		y++;
	}
}

static void		ft_write_pixels(t_env *e, t_bin coo, t_im ptr, t_floor f)
{
	ft_mlx_image_pixel_put(*e, coo.h, coo.v, RGB(\
		co(ptr.px[f.y * ptr.SL + (ptr.bpp / 8) * f.x + 2], f.coef), \
		co(ptr.px[f.y * ptr.SL + (ptr.bpp / 8) * f.x + 1], f.coef), \
		co(ptr.px[f.y * ptr.SL + (ptr.bpp / 8) * f.x + 0], f.coef)));
	if (e->roof == 1)
		ft_mlx_image_pixel_put(*e, coo.h, 300 - (coo.v - 300), RGB(\
			co(ptr.px[f.y * ptr.SL + (ptr.bpp / 8) * f.x + 0], f.coef), \
			co(ptr.px[f.y * ptr.SL + (ptr.bpp / 8) * f.x + 1], f.coef), \
			co(ptr.px[f.y * ptr.SL + (ptr.bpp / 8) * f.x + 2], f.coef)));
}

void			ft_floor(t_env *e, t_bin coo, float ray, t_im ptr)
{
	float	dist;
	t_floor	f;
	t_fbin	data;

	data.cos_ray_minus_cam_mid = cosf(dtor(ray - e->cam_mid));
	data.cos_ray = cosf(dtor(ray));
	data.sin_ray = sinf(dtor(ray));
	while (coo.v < 600)
	{
		dist = e->sol[coo.v - 300] / data.cos_ray_minus_cam_mid;
		dist = (e->zoom == 1 ? 2 * dist : dist);
		f.tx = e->cam_x + data.cos_ray * dist;
		f.ty = e->cam_y - data.sin_ray * dist;
		if (f.ty >= 0.0 && f.tx >= 0.0)
		{
			f.x = (int)(1414.0 * ft_fmodulo(f.tx, (float)e->BS) / (float)e->BS);
			f.y = (int)(1239.0 * ft_fmodulo(f.ty, (float)e->BS) / (float)e->BS);
			f.coef = 1.00000 - (dist / ((float)e->BS * e->shad_len));
			f.coef = (f.coef < 0.0) ? 0.0 : f.coef;
			f.coef += e->shad_coef;
			f.coef = (f.coef > 1.0) ? 1.0 : f.coef;
			ft_write_pixels(e, coo, ptr, f);
		}
		(coo.v)++;
	}
}

void			ft_draw_minimap(t_env *e, int x, int y)
{
	while (y < e->win_y)
	{
		x = 0;
		while (x < e->win_x)
		{
			if ((x % e->BS) == 0 || (y % e->BS) == 0)
				if (((x % e->BS) == 0 && \
					((e->map[y / e->BS][x / e->BS]).wall == 1 \
					|| (e->map[y / e->BS][x / e->BS - 1]).wall == 1)) \
					|| ((y % e->BS) == 0 && \
					((e->map[y / e->BS][x / e->BS]).wall == 1 || \
					(e->map[y / e->BS - 1][x / e->BS]).wall == 1)))
					ft_mlx_image_pixel_put(*e, x, y, 0xffffff);
			x++;
		}
		y++;
	}
}
