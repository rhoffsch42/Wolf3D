/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/25 01:51:17 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/06/04 10:35:21 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_calc_hor(t_env *e, float ray)
{
	ray == 360.00000 ? ray = 0.00000 : (void)ray;
	if (ray >= 0.0 && ray < 180.0)
	{
		e->hor->y = ((int)e->cam_y / e->BS) * e->BS - 0.0001;
		e->hor->ya = -(e->BS);
	}
	else if (ray >= 180.0 && ray < 360)
	{
		e->hor->y = ((int)e->cam_y / e->BS) * e->BS + e->BS;
		e->hor->ya = e->BS;
	}
	else
		exit(3);
	e->hor->xa = -(e->hor->ya) / tan(dtor(ray));
	e->hor->x = e->cam_x + (e->cam_y - e->hor->y) / tan(dtor(ray));
	while (e->hor->x >= 0 && e->hor->x < e->win_x && e->hor->y >= 0 && \
		e->hor->y < e->win_y && \
		(e->map[(int)(e->hor->y / e->BS)][(int)(e->hor->x / e->BS)]).wall == 0)
	{
		e->hor->x += e->hor->xa;
		e->hor->y += e->hor->ya;
	}
	ft_pos_overflow(e, e->hor);
}

void			ft_calc_ver(t_env *e, float ray)
{
	ray == 360.00000 ? ray = 0.00000 : (void)ray;
	if ((ray >= 270 && ray < 360) || (ray >= 0 && ray < 90))
	{
		e->ver->x = ((int)e->cam_x / e->BS) * e->BS + e->BS;
		e->ver->xa = (e->BS);
	}
	else if (ray >= 90 && ray < 270)
	{
		e->ver->x = ((int)e->cam_x / e->BS) * e->BS - 0.0001;
		e->ver->xa = -(e->BS);
	}
	else
		exit(4);
	e->ver->ya = -(e->ver->xa) * tan(dtor(ray));
	e->ver->y = e->cam_y + (e->cam_x - e->ver->x) * tan(dtor(ray));
	while (e->ver->x >= 0 && e->ver->x < e->win_x && e->ver->y >= 0 && \
		e->ver->y < e->win_y && \
		(e->map[(int)(e->ver->y / e->BS)][(int)(e->ver->x / e->BS)]).wall == 0)
	{
		e->ver->x += e->ver->xa;
		e->ver->y += e->ver->ya;
	}
	ft_pos_overflow(e, e->ver);
}

static void		ft_get_hor(t_env *e, float hori, int *h, float ray)
{
	e->dat->etage = ft_get_etage(e, 'x');
	e->dat->etage_min = e->etage_tmp;
	if (e->etage_tmp < e->dat->etage)
		e->etage_tmp = e->dat->etage;
	e->dat->distance = hori * cos(dtor(ray - e->cam_mid));
	e->dat->color = ft_give_color(e, ray, e->dat->distance, 'x');
	if (e->hor->x + e->hor->xa >= 0 && e->hor->x + e->hor->xa < e->win_x \
		&& e->hor->y + e->hor->ya >= 0 && e->hor->y + e->hor->ya < e->win_y)
	{
		*h = 1;
		e->hor->y += e->hor->ya;
		e->hor->x += e->hor->xa;
	}
	else
		*h = 0;
}

static void		ft_get_ver(t_env *e, float verti, int *v, float ray)
{
	e->dat->etage = ft_get_etage(e, 'y');
	e->dat->etage_min = e->etage_tmp;
	if (e->etage_tmp < e->dat->etage)
		e->etage_tmp = e->dat->etage;
	e->dat->distance = verti * cos(dtor(ray - e->cam_mid));
	e->dat->color = ft_give_color(e, ray, e->dat->distance, 'y');
	if (e->ver->x + e->ver->xa >= 0 && e->ver->x + e->ver->xa < e->win_x \
		&& e->ver->y + e->ver->ya >= 0 && e->ver->y + e->ver->ya < e->win_y)
	{
		*v = 1;
		e->ver->x += e->ver->xa;
		e->ver->y += e->ver->ya;
	}
	else
		*v = 0;
}

int				ft_get_walls(t_env *e, float ray, int x, t_bin bin)
{
	float	hori;
	float	verti;
	t_data	data;

	e->dat = &data;
	if (bin.h + bin.v != 2)
		return (0);
	e->floor_lvl += 1;
	ray == 360.00000 ? ray = 0.00000 : (void)ray;
	if (bin.v == 1 && (verti = ft_get_inter(e, e->ver->x, e->ver->y)) \
		< (hori = ft_get_inter(e, e->hor->x, e->hor->y)))
	{
		e->dat->coo = e->ver->y;
		e->dat->dir = 1;
		ft_get_ver(e, verti, &(bin.v), ray);
	}
	else if (bin.h == 1)
	{
		e->dat->coo = e->hor->x;
		e->dat->dir = 0;
		ft_get_hor(e, hori, &(bin.h), ray);
	}
	e->roof == 0 || e->texture == 0 ? ft_get_walls(e, ray, x, bin) : (void)hori;
	e->texture == 1 ? ft_texture(e, x, data, ray) : ft_draw_column(e, x, data);
	return (0);
}
