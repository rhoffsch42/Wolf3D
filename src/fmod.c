/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 14:01:32 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/06/01 14:56:20 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_error_fmod(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		ft_putnbr(result);
		ft_putstr(" FMOD error: ");
		ft_putstr(FMOD_ErrorString(result));
		ft_putchar('\n');
		exit(7);
	}
}

static void		ft_clear_songs(t_env *e)
{
	int	i;

	i = 0;
	while (i < NS)
	{
		e->song->list[i] = NULL;
		i++;
	}
}

static void		ft_get_song(t_env *e)
{
	FERR(FMOD_System_CreateSound(e->song->sys, "songs/ssb.mp3", \
		FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, \
		0, &(e->song->list[0])));
	FERR(FMOD_System_CreateSound(e->song->sys, "songs/fire.mp3", \
		FMOD_CREATESAMPLE, 0, &(e->song->list[1])));
	FERR(FMOD_System_CreateSound(e->song->sys, "songs/zoom.mp3", \
		FMOD_CREATESAMPLE, 0, &(e->song->list[2])));
	FERR(FMOD_System_CreateSound(e->song->sys, "songs/dzoom.mp3", \
		FMOD_CREATESAMPLE, 0, &(e->song->list[3])));
	FERR(FMOD_System_CreateSound(e->song->sys, "songs/walk.mp3", \
		FMOD_CREATESAMPLE | FMOD_LOOP_NORMAL, 0, &(e->song->list[4])));
	FERR(FMOD_System_CreateSound(e->song->sys, "songs/lighton.mp3", \
		FMOD_CREATESAMPLE, 0, &(e->song->list[5])));
	FERR(FMOD_System_CreateSound(e->song->sys, "songs/lightoff.mp3", \
		FMOD_CREATESAMPLE, 0, &(e->song->list[6])));
}

void			ft_launch_fmod(t_env *e)
{
	FERR(FMOD_System_Create(&(e->song->sys)));
	FERR(FMOD_System_Init(e->song->sys, 100, FMOD_INIT_NORMAL, NULL));
	ft_clear_songs(e);
	ft_get_song(e);
	FERR(FMOD_System_CreateChannelGroup(e->song->sys, "1", &e->song->chgrp[0]));
	FERR(FMOD_System_CreateChannelGroup(e->song->sys, "2", &e->song->chgrp[1]));
	FERR(FMOD_System_PlaySound(e->song->sys, FMOD_CHANNEL_FREE, \
		e->song->list[0], 1, &(e->song->chan[0])));
	FERR(FMOD_System_PlaySound(e->song->sys, FMOD_CHANNEL_FREE, \
		e->song->list[4], 1, &(e->song->chan[2])));
	FERR(FMOD_System_Update(e->song->sys));
	FERR(FMOD_Channel_SetChannelGroup(e->song->chan[0], e->song->chgrp[0]));
	FERR(FMOD_Channel_SetPaused(e->song->chan[0], 0));
	FERR(FMOD_Channel_SetPaused(e->song->chan[2], 1));
	FERR(FMOD_ChannelGroup_SetVolume(e->song->chgrp[0], 0.25f));
	FERR(FMOD_Sound_SetLoopCount(e->song->list[0], -1));
	FERR(FMOD_Sound_SetLoopCount(e->song->list[4], -1));
}

void			ft_close_fmod(t_env *e)
{
	FERR(FMOD_Sound_Release(e->song->list[0]));
	FERR(FMOD_Sound_Release(e->song->list[1]));
	FERR(FMOD_ChannelGroup_Release(e->song->chgrp[0]));
	FERR(FMOD_ChannelGroup_Release(e->song->chgrp[1]));
	FERR(FMOD_System_Close(e->song->sys));
	FERR(FMOD_System_Release(e->song->sys));
}
