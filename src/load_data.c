/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 19:29:01 by akolomoi          #+#    #+#             */
/*   Updated: 2019/08/25 19:29:02 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/alt.h"

//TODO: ща буит мясо

//TODO: gut_check()
//         ^^^ += (p|v|s_check) + scene_init()?
// страшна, вырубай

int 		load_data(char *fname, t_scene *scene)
{
	int 	fd;
	char	*line;
	t_v2f	*vert;
	int		n_vert;

	if ((fd = open(fname, O_RDONLY)) == -1)
		return (0);
	vert = NULL;
	n_vert = 0;
	while (get_next_line(fd, &line))
	{
		if (!gut_check(line, scene, vert, &n_vert))
			return (0);
	}
	return (1);
}
