/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 18:00:19 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/06/04 08:46:06 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_get_img(t_env *e)
{
	int	width;
	int	height;

	e->xpm[0] = mlx_xpm_file_to_image(e->mlx, "img/sky23.XPM", &width, &height);
	e->xpm[1] = mlx_xpm_file_to_image(e->mlx, "img/snipe.XPM", &width, &height);
	e->xpm[2] = mlx_xpm_file_to_image(e->mlx, "img/wall1.XPM", &width, &height);
	e->xpm[3] = mlx_xpm_file_to_image(e->mlx, "img/wall2.XPM", &width, &height);
	e->xpm[4] = mlx_xpm_file_to_image(e->mlx, "img/wall3.XPM", &width, &height);
	e->xpm[5] = mlx_xpm_file_to_image(e->mlx, "img/wall4.XPM", &width, &height);
	e->xpm[6] = mlx_xpm_file_to_image(e->mlx, "img/cry.XPM", &width, &height);
}
