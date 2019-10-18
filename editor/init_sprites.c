/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:52:48 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/18 19:52:50 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void				init_sprites(t_ed *e)
{
	DIR				*dir;
	struct dirent	*data;
	char 			*tmp[2];
	int 			i;

	dir = NULL;
	tmp[0] = "./textures/assets/assets/";
	reopen(&dir, tmp[0]);
	while ((data = readdir(dir)))
		if (bmp_check(data))
			e->n_sprites += 1;
	e->sprites = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * e->n_sprites);
	reopen(&dir, tmp[0]);
	i = 0;
	while ((data = readdir(dir)))
		if (bmp_check(data))
		{
			tmp[1] = ft_strjoin(tmp[0], data->d_name);
			read_bmp(&e->sprites[i++], tmp[1]);
		}
}
