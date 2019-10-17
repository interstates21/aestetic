/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_anims.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:13:08 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/17 19:13:10 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void		fetch_f(char ***names, struct dirent *data, int k)
{
	int 		i;

	i = -1;
	if (!bmp_check(data) || k > 49)
		return ;
	if (!(*names[k] = ))
}

void			load_names(t_ed *e, char *p, char ***names)
{
	DIR				*dir;
	struct dirent	*data;
	int 			k;

	dir = NULL;
	k = -1;
	reopen(&dir, p);
	if (!(*names = (char**)malloc(sizeof(char*) * 50)))
		print_err("malloc failed");
	while ((data = readdir(dir)) && (++k + 3))
		fetch_f(names, data, k);
	closedir(dir);

}
