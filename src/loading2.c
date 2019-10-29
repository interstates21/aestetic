/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:59:42 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 17:49:07 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void		print_1(t_env *d)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;
	t_vec2	v;

	s1 = "_____ _____  ________  ___  _   _ _   _ _   __ ________  ___";
	s2 = "|  _  \\  _  ||  _  |  \\/  | | \\ | | | | | | / /|  ___|  \\/  |";
	s3 = "| | | | | | || | | | .  . | |  \\| | | | | |/ / | |__ | .  . |";
	s4 = "| | | | | | || | | | |\\/| | | . ` | | | |    \\ |  __|| |\\/| |";
	v = new_v2int((WIDTH >> 1) - 56, 100);
	displaing_str(d, new_font(s1, v, RED, 2));
	v = move_down_vector2(v);
	displaing_str(d, new_font(s2, v, RED, 2));
	v = move_down_vector2(v);
	displaing_str(d, new_font(s3, v, RED, 2));
	v = move_down_vector2(v);
	displaing_str(d, new_font(s4, v, RED, 2));
}

void		print_2(t_env *d)
{
	char	*s1;
	char	*s2;
	char	*s3;
	t_vec2	v;

	s1 = "_____ _____  ________  ___  _   _ _   _ _   __ ________  ___";
	s2 = "| |/ /\\ \\_/ /\\ \\_/ / |  | | | |\\  | |_| | |\\  \\| |___| |  | |";
	s3 = "|___/  \\___/  \\___/\\_|  |_/ \\_| \\_/\\___/\\_| \\_/\\____/\\_|_/";
	v = new_v2int((WIDTH >> 1) - 56, 100);
	displaing_str(d, new_font(s1, v, RED, 2));
	v = move_down_vector2(v);
	displaing_str(d, new_font(s2, v, RED, 2));
	v = move_down_vector2(v);
	displaing_str(d, new_font(s3, v, RED, 2));
}

void		print_loading_ascii(t_env *d)
{
	print_1(d);
	print_2(d);
}
