/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 20:07:46 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/26 20:29:51 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	print_and_quit(t_data *d, const char *str)
{
	if (d->sdl.win)
		SDL_DestroyWindow(d->sdl.win);
	SDL_Quit();
	ft_putendl(ft_strjoin(("Good bye!"), str));
	exit(0);
}

void	print_err(const char *err)
{
	ft_putstr("Init Error = ");
	ft_putendl(err);
	system("leaks --quiet doom_nukem");
	exit(1);
}
