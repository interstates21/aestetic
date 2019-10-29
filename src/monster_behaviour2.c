/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_behaviour.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:39:48 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 17:41:33 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	month_ini(double rand, t_vec2f tmp, t_vec2f tmp2, t_monster *monster)
{
	monster->rot = rand;
	monster->dir = tmp;
	monster->timer = 100;
}
