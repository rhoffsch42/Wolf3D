/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 17:37:21 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/06/04 10:34:08 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <libft.h>
# include <fmod.h>
# include <fmod_errors.h>
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <time.h>
# include <sys/time.h>

# define RGB(r, g, b)(65536 * (int)(r) + 256 * (int)(g) + (int)(b))
# define BS		block_size
# define MVTS	mvt_speed
# define FERR	ft_error_fmod
# define NS		7
# define NX		7
# define SKY	3600.0
# define SL		sizeline

typedef struct	s_floor
{
	float	tx;
	float	ty;
	int		x;
	int		y;
	float	coef;
}				t_floor;

typedef struct	s_fbin
{
	float	cos_ray_minus_cam_mid;
	float	cos_ray;
	float	sin_ray;
}				t_fbin;

typedef struct	s_color
{
	int		red;
	int		green;
	int		blue;
}				t_color;

typedef struct	s_im
{
	int		bpp;
	int		sizeline;
	int		endian;
	char	*px;
}				t_im;

typedef struct	s_coo
{
	float	inter;
	float	y;
	float	x;
	float	xa;
	float	ya;
}				t_coo;

typedef struct	s_map
{
	int		end;
	int		wall;
	int		x;
	int		y;
}				t_map;

typedef struct	s_log
{
	int	dist;
	int	coo;
	int	base;
	int	inter;
}				t_log;

typedef struct	s_data
{
	float	coo;
	int		dir;
	int		color;
	int		ocolor;
	int		etage;
	int		etage_min;
	float	distance;
}				t_data;

typedef struct	s_bin
{
	int	h;
	int	v;
}				t_bin;

typedef struct	s_mod
{
	FMOD_SYSTEM			*sys;
	FMOD_CHANNEL		*chan[NS];
	FMOD_CHANNELGROUP	*chgrp[NS];
	FMOD_SOUND			*list[NS];
}				t_mod;

typedef struct	s_env
{
	t_log	*logs;
	void	*mlx;
	void	*win;
	void	*img;
	void	*xpm[NX];
	int		win_x;
	int		win_y;
	float	*sol;
	int		block_size;
	int		map_size;
	t_map	**map;
	int		mvt_speed;
	int		texture;
	float	cam_x;
	float	cam_y;
	float	fov;
	int		roof;
	int		zoom;
	float	cam_high;
	float	cam_mid;
	float	cam_low;
	float	ray_len;
	float	ray_mvt;
	int		screen;
	int		wall_dir;
	int		etage_tmp;
	int		floor_drawn;
	int		floor_lvl;
	t_coo	*hor;
	t_coo	*ver;
	t_data	*dat;
	float	shad_len;
	float	shad_coef;
	float	coef;
	float	time_start;
	float	time_period;
	t_mod	*song;
}				t_env;

int				ft_mlx_image_pixel_put(t_env e, int x, int y, int color);
void			ft_launch_mlx(t_env *e);
int				gnl(int const fd, char **line);

int				ft_expose_hook(t_env *e);
int				ft_expose_hook_tree(t_env *e);
int				ft_mouse_hook(int button, int x, int y, t_env *e);
int				ft_key_hook(int keycode, t_env *e);
int				ft_hook_mouse_move(int x, int y, t_env *e);
int				ft_hook_press(int keycode, t_env *e);
int				ft_no_key(t_env *e);

void			ft_move_right(t_env *e);
void			ft_move_left(t_env *e);
void			ft_move_up(t_env *e);
void			ft_move_down(t_env *e);
void			ft_zoom(t_env *e);
void			ft_fire(t_env *e);
void			ft_escape(t_env *e);

void			ft_draw(t_env *e);
void			ft_get_map(t_env *e);
float			rtod(float radians);
float			dtor(float degree);
float			ft_degree_scale(float degree);
float			ft_fmodulo(float n, float mod);
int				co(int val, float coef);

void			ft_find_wall(t_env *e, float ray, int x);
void			ft_draw_column(t_env *e, int x, t_data data);
int				ft_give_color(t_env *e, float ray, float distance, int dir);
void			ft_pos_overflow(t_env *e, t_coo *wall);
int				ft_get_walls(t_env *e, float ray, int x, t_bin bin);
float			ft_get_inter(t_env *e, float x, float y);
void			ft_calc_hor(t_env *e, float ray);
void			ft_calc_ver(t_env *e, float ray);
int				ft_get_etage(t_env *e, int dir);

void			ft_draw_cam(t_env *e);
void			ft_draw_minimap(t_env *e, int x, int y);
t_color			*ft_dec_to_rgb(int c);
t_map			*ft_iswall(t_env *e, int x, int y);
void			ft_calc_shader(t_env *e);

void			ft_fmod_playsound(t_env *e, int n, int ch, float vol);
void			ft_error_fmod(FMOD_RESULT result);
void			ft_launch_fmod(t_env *e);
void			ft_close_fmod(t_env *e);

void			ft_get_img(t_env *e);
void			ft_draw_crosshair(t_env *e);
void			ft_draw_scope(t_env *e);
void			ft_draw_bg(t_env *e, int x, int y);
void			ft_draw_floor2(t_env *e, int x, int y);
void			ft_draw_gun(t_env *e, int y, int diffx, int diffy);
void			ft_texture(t_env *e, int x, t_data data, float ray);
void			ft_floor(t_env *e, t_bin coo, float ray, t_im ptr);

#endif
