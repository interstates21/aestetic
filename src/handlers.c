/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 20:07:46 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/26 23:59:08 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	print_and_quit(t_data *d, const char *str)
{
	if (d->sdl.win)
		SDL_DestroyWindow(d->sdl.win);
	SDL_Quit();
	ft_putstr("Good Bye = ");
	ft_putendl(str);
	system("leaks --quiet doom_nukem");
	exit(0);
}

void	print_err(const char *err)
{
	ft_putstr("Init Error = ");
	ft_putendl(err);
	system("leaks --quiet doom_nukem");
	exit(1);
}
