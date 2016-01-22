/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/18 15:11:52 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/06/04 10:30:32 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	ft_expose_hook(t_env *e)
{
	ft_calc_shader(e);
	ft_draw(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

int	ft_hook_press(int keycode, t_env *e)
{
	if (keycode == 124 || keycode == 2)
		ft_move_right(e);
	if (keycode == 123 || keycode == 0)
		ft_move_left(e);
	if (keycode == 126 || keycode == 13)
		ft_move_up(e);
	if (keycode == 125 || keycode == 1)
		ft_move_down(e);
	return (keycode);
}

int	ft_hook_mouse_move(int x, int y, t_env *e)
{
	static int	old_x;
	static int	dir;

	if (x - old_x > 0)
	{
		e->ray_mvt = -2.5 * (e->fov / 60.0);
		dir = 1;
	}
	else if (x - old_x < 0)
	{
		e->ray_mvt = 2.5 * (e->fov / 60.0);
		dir = -1;
	}
	else if (dir > 0)
		e->ray_mvt = -2.5 * (e->fov / 60.0);
	else
		e->ray_mvt = 2.5 * (e->fov / 60.0);
	e->cam_mid += e->ray_mvt + y * 0;
	e->cam_high = (e->cam_mid + e->fov / 2.0);
	e->cam_low = (e->cam_high - e->fov);
	old_x = x;
	mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, e->win_x, e->win_y);
	ft_expose_hook(e);
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_env *e)
{
	(void)x;
	(void)y;
	if (button == 1)
		ft_fire(e);
	if (button == 2)
		ft_zoom(e);
	ft_expose_hook(e);
	return (0);
}

int	ft_key_hook(int keycode, t_env *e)
{
	if (keycode == 53)
		ft_escape(e);
	if (keycode == 15)
		e->roof = (e->roof == 1) ? 0 : 1;
	if ((keycode >= 123 && keycode <= 126) \
		|| (keycode >= 0 && keycode <= 2) || keycode == 13)
		FERR(FMOD_Channel_SetPaused(e->song->chan[2], 1));
	if (keycode == 38)
		e->shad_coef = 1.0;
	if (keycode == 45)
		e->shad_coef = 0.0;
	if (keycode == 4 && e->shad_coef < 1.0)
		e->shad_coef += 0.1;
	if (keycode == 11 && e->shad_coef > 0.1)
		e->shad_coef -= 0.1;
	if (keycode == 49)
	{
		e->shad_len = (e->shad_len == 10.0 ? 5.0 : 10.0);
		ft_fmod_playsound(e, e->shad_len == 10.0 ? 5 : 6, 1, 1.0);
	}
	if (keycode == 17)
		e->texture = (e->texture == 1 ? 0 : 1);
	ft_expose_hook(e);
	return (0);
}
