/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:45:02 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/29 16:45:04 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void		swap_vals(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

double		get_smh(t_vec3f v1, t_vec3f v2)
{
	double		res;
	t_vec3f		mns;

	mns = v3_min(v1, v2);
	res = vec3f_length(mns);
	return (res);
}

void		change_list(t_sprite_list *one, t_sprite_list *two,
t_sprite_list *prev)
{
	prev->next = two;
	one->next = two->next;
	two->next = one;
}

void		skip(void *smh)
{
	int		i;

	if (smh)
		return ;
	i = -3;
	while (++i < 3)
		;
}
