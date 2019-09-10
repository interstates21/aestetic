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

/*
 * на самом деле большая часть проверок больше не актуальна
 * тк есть куча проверок до вызова этих f()
 */

/*
 * приниает указатели на массивы, которые нужно обьеденить
 * возвращает указатель на массив (b + a)
 * или указатель на первый массив, если второй пуст
 * к моменту вызову этой функции, массив а не может быть пустым
 *
 * upd:
 *  ничего не возвращает
 *  сразу присваевает второму массиву нужное значение
 */
static void merge_arr(t_vt **a, t_vt **b, int ia, int *ib)
{
	t_vt *res;
	int c;

	res = (t_vt *)malloc(sizeof(t_vt) * (ia + *ib));
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

/*
 * принимает указатель на дабл, который надо считать,
 * строку с вершинами,
 * индекс последнего считаного символа
 */
int fetch_f(double *i, char *str, int *c)
{
	while (!ft_isdigit(str[*c]) && str[*c] ^ '-')
		*c = *c + 1;
	*i = atof(str + *c);
	*c += str[*c] == '-' ? 1 : 0;
	while (str[*c] && (ft_isdigit(str[*c]) || str[*c] == '.'))
		*c = *c + 1;
	return (1);
}

/*
 * примиает строку с вершинами
 * возвращает кол-во вершин (кол-во х - один у)
 * или 0 если
 * 		1) в числе больше 1 точки (13.42.53)
 * ?	кол-во координат не кратно двум?
 * > 	только первая координата в строке у, все остальные х
 * ? формат строки
 */
static int count_v(char *s)
{
	int db;
	int old;
	int res;
	int i;

	res = 0;
	db = 1;
	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		old = res;
		while (i >= 0 && (ft_isdigit(s[i]) || s[i] == '.'))
		{
			db = s[i] ^ '.' ? db : db - 1;
			if (db < 0)
				return (0);
			res = res ^ old ? res : res + 1;
			i--;
		}
		db = 1;
		i--;
	}
	return (res - 1);
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
 *
 * upd:
 *  принимает УКАЗАТЕЛЬ на МАССИВ (какой же я тупой)
 *  возвращает 1|0 вместо адресс|NULL
 */
int init_vertices(char *str, t_vt **arr, int *n_v)
{
	t_vt *res;
	int v;
	int i;
	int c;
	double y;

	if (!str || ((v = count_v(str)) < 1))
		return (0);
	res = (t_vt *)malloc(sizeof(t_vt) * v);
	i = -1;
	c = 0;
	fetch_f(&y, str, &c);
	while (++i < v)
	{
		res[i].y = y;
		if (fetch_f(&res[i].x, str, &c))
			continue;
		free(res);
		return (0);
	}
	merge_arr(&res, arr, v, n_v);
	return (1);
}
