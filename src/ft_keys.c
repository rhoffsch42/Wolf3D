/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 02:25:32 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/06/01 21:18:04 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_move_right(t_env *e)
{
	float	tmpx;
	float	tmpy;

	if (e->cam_x > (float)e->MVTS && e->cam_y > (float)e->MVTS && \
		e->cam_x < e->win_x - e->MVTS && e->cam_y < e->win_y - e->MVTS)
	{
		FERR(FMOD_Channel_SetPaused(e->song->chan[2], 0));
		tmpx = e->cam_x + cos(dtor(e->cam_mid - 90.0)) * (float)e->MVTS;
		tmpy = e->cam_y - sin(dtor(e->cam_mid - 90.0)) * (float)e->MVTS;
		if (ft_iswall(e, (int)tmpx, (int)tmpy) == NULL)
		{
			e->cam_x = tmpx;
			e->cam_y = tmpy;
		}
		else if (ft_iswall(e, (int)tmpx, (int)e->cam_y) == NULL)
			e->cam_x = tmpx;
		else if (ft_iswall(e, (int)e->cam_x, (int)tmpy) == NULL)
			e->cam_y = tmpy;
		mlx_destroy_image(e->mlx, e->img);
		e->img = mlx_new_image(e->mlx, e->win_x, e->win_y);
		ft_expose_hook(e);
	}
}

void	ft_move_left(t_env *e)
{
	float	tmpx;
	float	tmpy;

	if (e->cam_x > (float)e->MVTS && e->cam_y > (float)e->MVTS && \
		e->cam_x < e->win_x - e->MVTS && e->cam_y < e->win_y - e->MVTS)
	{
		FERR(FMOD_Channel_SetPaused(e->song->chan[2], 0));
		tmpx = e->cam_x + cos(dtor(e->cam_mid + 90.0)) * (float)e->MVTS;
		tmpy = e->cam_y - sin(dtor(e->cam_mid + 90.0)) * (float)e->MVTS;
		if (ft_iswall(e, (int)tmpx, (int)tmpy) == NULL)
		{
			e->cam_x = tmpx;
			e->cam_y = tmpy;
		}
		else if (ft_iswall(e, (int)tmpx, (int)e->cam_y) == NULL)
			e->cam_x = tmpx;
		else if (ft_iswall(e, (int)e->cam_x, (int)tmpy) == NULL)
			e->cam_y = tmpy;
		mlx_destroy_image(e->mlx, e->img);
		e->img = mlx_new_image(e->mlx, e->win_x, e->win_y);
		ft_expose_hook(e);
	}
}

void	ft_move_up(t_env *e)
{
	float	tmpx;
	float	tmpy;

	if (e->cam_x > (float)e->MVTS && e->cam_y > (float)e->MVTS && \
		e->cam_x < e->win_x - e->MVTS && e->cam_y < e->win_y - e->MVTS)
	{
		FERR(FMOD_Channel_SetPaused(e->song->chan[2], 0));
		tmpx = e->cam_x + cos(dtor(e->cam_mid)) * (float)e->MVTS;
		tmpy = e->cam_y - sin(dtor(e->cam_mid)) * (float)e->MVTS;
		if (ft_iswall(e, (int)tmpx, (int)tmpy) == NULL)
		{
			e->cam_x = tmpx;
			e->cam_y = tmpy;
		}
		else if (ft_iswall(e, (int)tmpx, (int)e->cam_y) == NULL)
			e->cam_x = tmpx;
		else if (ft_iswall(e, (int)e->cam_x, (int)tmpy) == NULL)
			e->cam_y = tmpy;
		mlx_destroy_image(e->mlx, e->img);
		e->img = mlx_new_image(e->mlx, e->win_x, e->win_y);
		ft_expose_hook(e);
	}
}

void	ft_move_down(t_env *e)
{
	float	tmpx;
	float	tmpy;

	if (e->cam_x > (float)e->MVTS && e->cam_y > (float)e->MVTS && \
		e->cam_x < e->win_x - e->MVTS && e->cam_y < e->win_y - e->MVTS)
	{
		FERR(FMOD_Channel_SetPaused(e->song->chan[2], 0));
		tmpx = e->cam_x - cos(dtor(e->cam_mid)) * (float)e->MVTS;
		tmpy = e->cam_y + sin(dtor(e->cam_mid)) * (float)e->MVTS;
		if (ft_iswall(e, (int)tmpx, (int)tmpy) == NULL)
		{
			e->cam_x = tmpx;
			e->cam_y = tmpy;
		}
		else if (ft_iswall(e, (int)tmpx, (int)e->cam_y) == NULL)
			e->cam_x = tmpx;
		else if (ft_iswall(e, (int)e->cam_x, (int)tmpy) == NULL)
			e->cam_y = tmpy;
		mlx_destroy_image(e->mlx, e->img);
		e->img = mlx_new_image(e->mlx, e->win_x, e->win_y);
		ft_expose_hook(e);
	}
}

void	ft_zoom(t_env *e)
{
	e->fov = e->fov == 30 ? 60 : 30;
	e->zoom = e->zoom == 1 ? 0 : 1;
	ft_fmod_playsound(e, e->zoom == 1 ? 2 : 3, 1, 1.0);
	e->cam_high = (e->cam_mid + e->fov / 2.0);
	e->cam_low = (e->cam_high - e->fov);
	e->ray_len = e->fov / (float)e->win_x;
	e->screen = (e->win_x / 2) / tan(dtor((e->fov / 2)));
	mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, e->win_x, e->win_y);
	ft_expose_hook(e);
}
