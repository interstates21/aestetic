/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:38:46 by akolomoi          #+#    #+#             */
/*   Updated: 2019/09/23 16:38:47 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/alt.h"

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

int			clampi(int i, int big, int low)//
{
	return (clamp(i, big, low));//
}
