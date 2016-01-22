/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 17:36:08 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/06/01 18:57:16 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_env	*ft_malloc_env(void)
{
	t_env	*e;

	e = (t_env*)malloc(sizeof(t_env));
	e->logs = (t_log*)malloc(sizeof(t_log));
	e->hor = (t_coo*)malloc(sizeof(t_coo));
	e->ver = (t_coo*)malloc(sizeof(t_coo));
	e->song = (t_mod*)malloc(sizeof(t_mod));
	e->sol = (float*)malloc(sizeof(float) * 300);
	return (e);
}

static void		ft_get_sol(t_env *e)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open("floor.coo", O_RDONLY);
	while (gnl(fd, &line) > 0)
	{
		e->sol[i] = ft_atoi(line);
		e->sol[i] += (float)ft_atoi(ft_strchr(line, '.') + 1) / 1000000.0;
		i++;
	}
	free(line);
	close(fd);
}

int				main(void)
{
	t_env		*e;

	e = ft_malloc_env();
	ft_launch_fmod(e);
	ft_get_map(e);
	ft_get_sol(e);
	if ((e->mlx = mlx_init()) == NULL)
	{
		ft_putendl("mlx_init failed");
		exit(1);
	}
	ft_get_img(e);
	ft_launch_mlx(e);
	mlx_key_hook(e->win, ft_key_hook, e);
	mlx_hook(e->win, 6, 1L << 6, ft_hook_mouse_move, e);
	mlx_hook(e->win, 2, 1L << 0, ft_hook_press, e);
	mlx_mouse_hook(e->win, ft_mouse_hook, e);
	mlx_expose_hook(e->win, ft_expose_hook, e);
	mlx_loop(e->mlx);
	return (0);
}
