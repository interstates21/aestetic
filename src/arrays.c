/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 23:49:29 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/28 18:45:50 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	merge_vector_arr(t_vec3f **a, t_vec3f **b, int ia, int *ib)
{
	t_vec3f	*res;
	int		c;

	res = (t_vec3f *)malloc(sizeof(t_vec3f) * (ia + *ib));
	c = -1;
	while (++c < *ib)
	{
		res[c] = (*b)[c];
	}
	c -= 1;
	while (++c < ia + *ib)
		res[c] = (*a)[c - *ib];
	*ib += ia;
	if (*a)
		free(*a);
	if (*b)
		free(*b);
	*b = res;
	*a = NULL;
}
