/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 11:33:27 by adespond          #+#    #+#             */
/*   Updated: 2019/06/25 14:32:57 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <SDL2/SDL.h>
# include <SDL_image.h>
# include <SDL_mixer.h>
//# include "libft.h"
# include <stdio.h>
# include <string.h>
# include <math.h>

# define WIDTH 800
# define HEIGHT 600
# define TEXWIDTH 64
# define TEXHEIGHT 64

typedef struct		s_struct
{
	SDL_Window	*window;
	SDL_Surface	*surface;
	SDL_Surface	**wall_texture;
	Mix_Music	*music;
	double		player_posx;
	double		player_posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		camerax;
	double		raydirx;
	double		raydiry;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	double		movespeed;
	double		olddirx;
	double		oldplanex;
	double		rotspeed;
	double		floorx;
	double		floory;
	double		distwall;
	double		distplayer;
	double		currentdist;
	double		wallx;
	double		weid;
	double		currentfloorx;
	double		currentfloory;
	char		*name;
	int			**worldmap;
	int			plpos;
	int			floorxx;
	int			floorxy;
	int			mapheig;
	int			mapwidt;
	int			stepx;
	int			stepy;
	int			side;
	int			x;
	int			mapx;
	int			mapy;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			color;
	int			stop;
	int			up;
	int			down;
	int			right;
	int			left;
	int			fd;
	int			lines;
	int			check;
	int			chars;
	int			d;
	int			texy;
	int			texnum;
	int			texx;
	int			space;
	int			mus;
}					t_struct;

void				raycast(t_struct *ray);
void				hook(t_struct *ray);
void				ft_move(t_struct *ray);
void				init(t_struct *wl);
void				ft_move1(t_struct *ray);
void				sidefloor(t_struct *ray);
void				iter(t_struct *ray);
void				clearsdl(t_struct *ray);
int					maps(t_struct *parse);
int					sd_init(t_struct *ray);
int					checkmaps(t_struct *ch);
int					checkwall(t_struct *wall);
int					music(t_struct *ray);
void				drawroof(SDL_Surface *surface, SDL_Surface *tex,
	t_struct *ray);

#endif
