/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 09:21:09 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/06/04 10:36:56 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ft_draw_floor(t_env *e, int x, int end, float ray)
{
	t_bin	coo;
	t_im	ptr;

	e->floor_drawn += 1;
	if (e->floor_drawn == e->floor_lvl)
	{
		ptr.px = mlx_get_data_addr(e->xpm[6], \
			&ptr.bpp, &ptr.sizeline, &ptr.endian);
		coo.h = x;
		coo.v = end + 1;
		ft_floor(e, coo, ray, ptr);
	}
}

static void		ft_shad_coef(t_env *e, t_data data)
{
	e->coef = 1.00000 - (data.distance / ((float)e->BS * e->shad_len));
	e->coef = (e->coef < 0.0) ? 0 : e->coef;
	e->coef += e->shad_coef;
	e->coef = (e->coef > 1.0) ? 1 : e->coef;
}

static int		ft_give_texture(int color)
{
	if (color == 0xFF0000)
		return (4);
	else if (color == 0x00FF00)
		return (3);
	else if (color == 0x0000FF)
		return (2);
	else if (color == 0xFF8000)
		return (5);
	else
		exit(8);
	return (4);
}

static int		ft_getpx(t_env *e, t_data data, float ratioy)
{
	t_im	ptr;
	float	ratiox;
	int		x;
	int		y;

	ratiox = ft_fmodulo(data.coo, (float)e->BS) / (float)e->BS;
	ptr.px = mlx_get_data_addr(e->xpm[ft_give_texture(data.ocolor)], \
		&ptr.bpp, &ptr.sizeline, &ptr.endian);
	x = (int)(829.0 * ratiox);
	y = (int)(764.0 * ratioy);
	return (RGB(co(ptr.px[y * ptr.sizeline + (ptr.bpp / 8) * x + 2], e->coef), \
	co(ptr.px[y * ptr.sizeline + (ptr.bpp / 8) * x + 1], e->coef), \
	co(ptr.px[y * ptr.sizeline + (ptr.bpp / 8) * x + 0], e->coef)));
}

void			ft_texture(t_env *e, int x, t_data data, float ray)
{
	int		start;
	int		end;
	float	height;
	int		tmp;
	int		y;

	height = ((float)(e->screen) * (float)e->BS) / (data.distance);
	start = (int)(-height) / 2 + e->win_y / 2;
	y = (start < 0) ? 0 : start;
	end = (int)(height) / 2 + e->win_y / 2;
	(end >= e->win_y) ? end = e->win_y - 1 : (void)end;
	ft_shad_coef(e, data);
	while (y != end)
	{
		tmp = data.etage - 1;
		while (tmp + 1 > data.etage_min)
		{
			if (y - ((int)height - 2) * tmp >= 0)
				ft_mlx_image_pixel_put(*e, x, y - (height - 2) * tmp, \
					ft_getpx(e, data, (float)(y - start) / height));
			tmp--;
		}
		y++;
	}
	(e->texture == 1) ? ft_draw_floor(e, x, end, ray) : (void)y;
}
