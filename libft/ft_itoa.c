/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 16:16:20 by akolomoi          #+#    #+#             */
/*   Updated: 2018/10/28 16:16:21 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int nbr)
{
	char	*buff;
	int		i;
	long	b;
	int		pos;

	b = (nbr < 0) ? -(long)nbr : nbr;
	pos = (nbr < 0) ? -1 : 0;
	i = (pos == -1) ? 2 : 1;
	while ((b /= 10) >= 1)
		i++;
	buff = (char*)malloc(sizeof(char) * (i + 1));
	buff[i] = '\0';
	b = (nbr < 0) ? -(long)nbr : nbr;
	while (i-- + pos)
	{
		buff[i] = b % 10 + '0';
		b /= 10;
	}
	(i == 0) ? buff[i] = '-' : 0;
	return (buff);
}
