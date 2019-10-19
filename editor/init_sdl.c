/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:09:50 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/17 16:09:51 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void			reopen(DIR **dir, const char *path)
{
	if (*dir)
	{
		closedir(*dir);
		*dir = NULL;
	}
	if (!(*dir = opendir(path)))
		print_err("opening textures dir failed");
}

void			reopen_fd(int *fd, const char *path)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	if ((*fd = open(path, O_RDONLY)) == -1)
		print_err("opening file failed");
}


// void	init_sdl(t_sdl *sdl)
// {
// 	SDL_Init(SDL_INIT_EVERYTHING);
// 	if (!(sdl->win = SDL_CreateWindow("doom_nukem editor", SDL_WINDOWPOS_UNDEFINED,
// 		SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, 0)))
// 		print_err(SDL_GetError());
// 	if (!(sdl->screen = SDL_GetWindowSurface(sdl->win)))
// 		print_err(SDL_GetError());
// }
