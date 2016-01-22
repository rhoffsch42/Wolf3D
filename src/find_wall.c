/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/18 19:15:58 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/05/30 13:22:18 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_pos_overflow(t_env *e, t_coo *wall)
{
	(wall->x < 0) ? wall->x = 0 : (void)wall->x;
	(wall->x >= e->win_x) ? wall->x = e->win_x - 1 : (void)wall->x;
	(wall->y < 0) ? wall->y = 0 : (void)wall->y;
	(wall->y >= e->win_y) ? wall->y = e->win_y - 1 : (void)wall->y;
}

float			ft_get_inter(t_env *e, float x, float y)
{
	float	diffx;
	float	diffy;
	float	inter;

	diffx = fabs(e->cam_x - x);
	diffx = diffx * diffx;
	diffy = fabs(e->cam_y - y);
	diffy = diffy * diffy;
	inter = sqrt(diffx + diffy);
	return (inter);
}

static float	ft_get_wall_horizontal(t_env *e, float ray)
{
	ray == 360.0000000 ? ray = 0.000000 : (void)ray;
	if (ray >= 0.0 && ray < 180.0)
	{
		e->hor->y = ((int)e->cam_y / e->BS) * e->BS - 0.000001;
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
	e->hor->inter = ft_get_inter(e, e->hor->x, e->hor->y);
	return (e->hor->inter);
}

static float	ft_get_wall_vertical(t_env *e, float ray)
{
	ray == 360.0000000 ? ray = 0.000000 : (void)ray;
	if ((ray >= 270 && ray < 360) || (ray >= 0 && ray < 90))
	{
		e->ver->x = ((int)e->cam_x / e->BS) * e->BS + e->BS;
		e->ver->xa = (e->BS);
	}
	else if (ray >= 90 && ray < 270)
	{
		e->ver->x = ((int)e->cam_x / e->BS) * e->BS - 0.000001;
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
	e->ver->inter = ft_get_inter(e, e->ver->x, e->ver->y);
	return (e->ver->inter);
}

void			ft_find_wall(t_env *e, float ray, int x)
{
	float	ray_scale;
	t_data	data;

	ray_scale = ft_degree_scale(ray);
	ft_get_wall_horizontal(e, ray_scale);
	ft_get_wall_vertical(e, ray_scale);
	if (e->hor->inter <= e->ver->inter)
	{
		data.distance = e->hor->inter;
		data.color = ft_give_color(e, ray_scale, data.distance, 'x');
		data.etage = ft_get_etage(e, 'x') - 1;
	}
	else
	{
		data.distance = e->ver->inter;
		data.color = ft_give_color(e, ray_scale, data.distance, 'y');
		data.etage = ft_get_etage(e, 'y') - 1;
	}
	data.distance = data.distance * cos(dtor(ray - e->cam_mid));
	ft_draw_column(e, x, data);
}
