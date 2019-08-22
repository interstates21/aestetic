/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:43:15 by akolomoi          #+#    #+#             */
/*   Updated: 2019/08/22 17:43:17 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/alt.h"

//TODO: merge_arr()
/*
 * принимает указатель на вершину, которую надо считать,
 * строку с вершинами,
 * индекс
 */
static int	fetch_v2f(t_v2f *v, char *str, int *c)
{
	if (*c == ft_strlen(str))
		return (0);
	while (!ft_isdigit(str[*c]) && str[*c] ^ '-')
		*c += 1;
	v->x = atof(str + *c);
	while(str[*c] ^ ' ' && str[*c] ^ '\t')
		*c += 1;
	while (!ft_isdigit(str[*c]) && str[*c] ^ '-')
		*c += 1;
	v->y = atof(str + *c);
	while(str[*c] && str[*c] ^ ' ' && str[*c] ^ '\t')
		*c += 1;
	return (1);
}

/*
 * примиает строку с вершинами
 * возвращает кол-во вершин
 * или 0 если
 * 		1) в числе больше 1 точки (13.42.53)
 * ?	2) кол-во координат не кратно двум?
 * ? формат строки
 */
static int	count_v(char *s)
{
	int		db;
	int 	old;
	int 	res;

	res = 0;
	db = 1;
	while (*s)
	{
		old = res;
		while (ft_isdigit(*s) || *s == '.')
		{
			db = *s ^ '.' ? db : db - 1 ;
			if (db < 0)
				return (0);
			res = res ^ old ? res : res + 1;
			s++;
		}
		db = 1;
		s++;
	}
	return (res % 2 ? 0 : res / 2);
}

/*
 * бисквит:
 *	реалочит массив вершин, обновляет
 *	NumVertices с каждым вызовом
 * ----
 * принимает указатель на строку, которую вернул гнл,
 * массив с вершинами (NULL если пока пуст),
 * NumVertices через указатель.
 *
 * *реаллочит* массив вершин, добавляя вершины со строки
 * возвращает указатель на новый массив
 * или NULL если
 * 		1) в строке мало параметров
 * 		2) параметры записаны в неверном формате / передана пустая строка
 *
 * ? какой формат входящей строки
 * ? ft_atof()
 */
t_v2f		*init_vertices(char *str, t_v2f *arr, int *NumVertices)
{
	t_v2f	*res;
	int 	v;
	int 	i;
	int 	c;
	char	**start;

	if (!str || (v = count_v(str) < 1))
		return (NULL);
	res = (t_v2f*)malloc(sizeof(t_v2f) * v);
	i = -1;
	c = 0;
	start = &str;
	while (++i < v)
	{
		if (fetch_v2f(&res[i], str, &c))
			continue ;
		str = start;
		free(res);
		return (NULL);
	}
	str = *start;
	return (merge_arr(res, arr, v, NumVertices));
}
