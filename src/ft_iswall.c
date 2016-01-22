/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/24 18:38:53 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/05/30 20:29:50 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_map		*ft_iswall(t_env *e, int x, int y)
{
	if (x >= 0 && x < e->win_x && y >= 0 && y < e->win_y && \
		(e->map[y / e->BS][x / e->BS]).wall != 0)
		return (&(e->map[y / e->BS][x / e->BS]));
	return (NULL);
}

int			ft_get_etage(t_env *e, int dir)
{
	t_map	*ptr;

	if (dir == 'x')
		ptr = ft_iswall(e, e->hor->x, e->hor->y);
	else
		ptr = ft_iswall(e, e->ver->x, e->ver->y);
	return (ptr->wall);
}
