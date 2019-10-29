/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_font.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:59:42 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 15:53:35 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

t_font	new_font(char *str, t_vec2 v, Uint32 color, int scale)
{
	t_font	f;

	f.str = str;
	f.x = v.x;
	f.y = v.y;
	f.color = color;
	f.scale = scale;
	return (f);
}
