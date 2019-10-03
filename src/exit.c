/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 00:00:29 by nallani           #+#    #+#             */
/*   Updated: 2019/07/04 14:14:50 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	proper_exit(t_data *d)
{
	SDL_DestroyWindow(d->win);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

void	err_exit(const char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
