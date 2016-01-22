/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 12:18:57 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/06/02 20:47:38 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_add_block(t_env *e, char *str, int i, int j)
{
	(e->map[i][j]).wall = str[0] - 48;
	(e->map[i][j]).x = i;
	(e->map[i][j]).y = j;
	(e->map[i][j]).end = 0;
}

static void	ft_add_line(t_env *e, char *str, int i)
{
	int		j;
	char	**tab;

	tab = ft_strsplit(str, ' ');
	j = 0;
	while (tab[j] != NULL)
	{
		ft_add_block(e, tab[j], i, j);
		free(tab[j]);
		j++;
	}
	(e->map[i][j]).end = 1;
	(e->map[i][j]).wall = 0;
	(e->map[i][j]).x = 0;
	(e->map[i][j]).y = 0;
	free(tab);
}

static int	ft_get_width(char *str)
{
	int	i;
	int	len;

	len = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			len++;
		i++;
	}
	return (len);
}

static int	ft_get_height(void)
{
	char	*str;
	int		fd;
	int		i;

	str = (char*)malloc(sizeof(char) * 10001);
	fd = open("maps/level0.map", O_RDONLY);
	if ((i = read(fd, str, 10000)) == -1)
		exit(2);
	str[i] = '\0';
	close(fd);
	fd = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			fd++;
		i++;
	}
	free(str);
	return (fd);
}

void		ft_get_map(t_env *e)
{
	char	*str;
	int		fd;
	int		i;

	e->map = (t_map**)malloc(sizeof(t_map*) * ft_get_height() + 1);
	fd = open("maps/level0.map", O_RDONLY);
	i = 0;
	while (get_next_line(fd, &str) == 1)
	{
		e->map[i] = (t_map*)malloc(sizeof(t_map) * ft_get_width(str) + 1);
		ft_add_line(e, str, i);
		i++;
	}
	e->map[i] = NULL;
	e->map_size = ft_get_width(str);
	free(str);
	close(fd);
}
