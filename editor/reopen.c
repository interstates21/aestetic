/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reopen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:09:50 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/29 22:55:39 by bdeomin          ###   ########.fr       */
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
