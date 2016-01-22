/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/18 07:39:19 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/04/01 00:33:32 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcolor(char *c1, char *color, char *c2)
{
	char	*tmp;

	tmp = ft_strnew(7);
	ft_strcat(tmp, c1);
	ft_strcat(tmp, color);
	ft_strcat(tmp, c2);
	ft_putstr(tmp);
	return (tmp);
}

void	ft_putstr_color(char *str, char *color)
{
	COLOR(color);
	ft_putstr(str);
	COLOR(WHITE);
}
