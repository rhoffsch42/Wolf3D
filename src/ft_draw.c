/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/16 21:10:59 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/06/04 10:33:45 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_give_color(t_env *e, float ray, float distance, int dir)
{
	int		color;
	t_color	*tmp;
	float	coef;

	if (ray >= 0.0 && ray < 90.0)
		color = (dir == 'x') ? 0xFF0000 : 0x00FF00;
	else if (ray >= 90.0 && ray < 180.0)
		color = (dir == 'x') ? 0xFF0000 : 0xFF8000;
	else if (ray >= 180.0 && ray < 270.0)
		color = (dir == 'x') ? 0x0000FF : 0xFF8000;
	else
		color = (dir == 'x') ? 0x0000FF : 0x00FF00;
	e->dat->ocolor = color;
	coef = 1.00000 - (distance / ((float)e->BS * e->shad_len));
	coef = ((coef < 0.0) ? 0 : coef);
	coef += e->shad_coef;
	coef = ((coef > 1.0) ? 1 : coef);
	tmp = ft_dec_to_rgb(color);
	tmp->red = (int)((float)tmp->red * coef);
	tmp->green = (int)((float)tmp->green * coef);
	tmp->blue = (int)((float)tmp->blue * coef);
	color = RGB(tmp->red, tmp->green, tmp->blue);
	free(tmp);
	return (color);
}

void		ft_draw_column(t_env *e, int x, t_data data)
{
	int		start;
	int		end;
	float	height;
	int		tmp;

	height = ((float)(e->screen) * (float)e->BS) / (data.distance);
	start = (int)(-height) / 2 + e->win_y / 2;
	(start < 0) ? start = 0 : (void)start;
	end = (int)(height) / 2 + e->win_y / 2;
	(end >= e->win_y) ? end = e->win_y - 1 : (void)end;
	while (start != end)
	{
		tmp = data.etage - 1;
		while (tmp + 1 > data.etage_min)
		{
			if (start - (height - 2) * tmp >= 0)
				ft_mlx_image_pixel_put(*e, x, start - (height - 2) * tmp,
					data.color);
			tmp--;
		}
		start++;
	}
}

static void	ft_build_bin(t_bin *bin)
{
	bin->h = 1;
	bin->v = 1;
}

static void	ft_draw_wall(t_env *e, int marge)
{
	float	ray;
	int		x;
	t_bin	*bin;

	bin = (t_bin*)malloc(sizeof(t_bin));
	ft_build_bin(bin);
	ray = e->cam_low;
	x = e->win_x - 1;
	marge = e->win_x / 2 - (int)(((float)e->win_x * 3.0) / 8.0);
	while (ray <= e->cam_high)
	{
		if ((e->zoom == 0) || (ray <= e->cam_high && e->zoom == 1 \
			&& x < e->win_x - marge && x > marge))
		{
			e->floor_drawn = 0;
			e->floor_lvl = 0;
			e->etage_tmp = 0;
			ft_calc_hor(e, ft_degree_scale(ray));
			ft_calc_ver(e, ft_degree_scale(ray));
			ft_get_walls(e, ft_degree_scale(ray), x, *bin);
		}
		ray += e->ray_len;
		x--;
	}
	free(bin);
}

void		ft_draw(t_env *e)
{
	if (e->roof == 0 || e->texture == 0)
		ft_draw_bg(e, 0, 0);
	ft_draw_wall(e, 0);
	if (e->zoom == 0)
	{
		ft_draw_crosshair(e);
		ft_draw_gun(e, 0, e->win_x - 280, e->win_y - 190);
	}
	else
		ft_draw_scope(e);
}
