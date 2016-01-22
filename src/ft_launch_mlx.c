/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 17:49:40 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/06/04 09:52:42 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_no_key(t_env *e)
{
	mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, e->win_x, e->win_y);
	ft_expose_hook(e);
	return (0);
}

void		ft_calc_shader(t_env *e)
{
	struct timeval	tv;
	float			diff;
	float			cf;

	gettimeofday(&tv, NULL);
	diff = (float)(tv.tv_sec - 1448000000) + (float)tv.tv_usec / 1000000.0f;
	diff = ft_fmodulo(diff - e->time_start, (e->time_period));
	cf = fabs((e->time_period / 2.0) - diff);
	e->shad_coef = cf / (e->time_period / 2.0);
	if (e->shad_coef > 0.99999)
		e->shad_coef = 1.0;
}

void		ft_launch_mlx(t_env *e)
{
	e->win_x = 600;
	e->win_y = 600;
	e->img = mlx_new_image(e->mlx, e->win_x, e->win_y);
	ft_draw_bg(e, 0, 0);
	e->win = mlx_new_window(e->mlx, e->win_x, e->win_y, "Wolf3d");
	e->BS = e->win_x / e->map_size;
	e->mvt_speed = 2;
	e->texture = 1;
	e->fov = 60;
	e->zoom = 0;
	e->roof = 0;
	e->cam_x = 520.0;
	e->cam_y = 50.0;
	e->cam_mid = 75;
	e->cam_high = (e->cam_mid + e->fov / 2.0);
	e->cam_low = (e->cam_high - e->fov);
	e->ray_len = e->fov / (float)e->win_x;
	e->screen = (e->win_x / 2) / tan(dtor((e->fov / 2)));
	e->time_start = (float)(time(NULL) - 1448000000);
	e->time_period = 30.0;
	e->shad_len = 5.0;
	ft_calc_shader(e);
}
