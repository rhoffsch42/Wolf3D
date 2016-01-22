/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/31 22:29:06 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/06/01 13:17:40 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_fmod_playsound(t_env *e, int n, int ch, float vol)
{
	FERR(FMOD_System_PlaySound(e->song->sys, FMOD_CHANNEL_FREE, \
		e->song->list[n], 1, &(e->song->chan[ch])));
	FERR(FMOD_System_Update(e->song->sys));
	FERR(FMOD_Channel_SetChannelGroup(e->song->chan[ch], e->song->chgrp[ch]));
	FERR(FMOD_Channel_SetPaused(e->song->chan[ch], 0));
	FERR(FMOD_ChannelGroup_SetVolume(e->song->chgrp[ch], vol));
}

void	ft_fire(t_env *e)
{
	ft_fmod_playsound(e, 1, 1, 1.0);
}

void	ft_escape(t_env *e)
{
	ft_close_fmod(e);
	exit(0);
}
