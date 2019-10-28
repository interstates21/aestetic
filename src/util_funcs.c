/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_allocators.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 23:49:29 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/26 23:49:31 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

int			maxi(int a, int b)
{
	return (a > b ? a : b);
}

int			mini(int a, int b)
{
	return (a < b ? a : b);
}

double		minf(double a, double b)
{
	return (a < b ? a : b);
}

double		maxf(double a, double b)
{
	return (a > b ? a : b);
}

int			clampi(int i, int big, int low)
{
	return (mini(maxi(i, big), low));
}
