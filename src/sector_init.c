/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:25:44 by akolomoi          #+#    #+#             */
/*   Updated: 2019/08/24 19:25:45 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/alt.h"

/*
 * принимает указатель на новый массив, на старый массив (или NULL),
 * кол-во копируемых елементов
 *
 * копирует старый массив в новый
 * чистит старый массив (если он был)
 */
static void		copy_arr(t_sector *a, t_sector *b, int s)
{
	printf("    +copy_arr\n");
	int			i;

	i = -1;
	while (++i < s)
		a[i] = b[i];
	if (b)
		free(b);
	printf("    -copy_arr\n");
}

// считает кол-во интов в строке после с
static int		*num_ints(char *s, int c, int *m)
{
	printf("    +num_ints\n");
	int			db;

	db = 0;
	*m = 0;
	while (s[c])
	{
		if (!ft_isdigit(s[c]) && s[c] ^ '-')
			db = 0;
		else if (!db)
		{
			*m += 1;
			db = 1;
		}
		c++;
	}
	printf("    -num_ints\n");
	return (m);
}

/*
 * принимает строку и индекс в ней
 * возвращает первый найденый инт и сдвигает индекс в конец инта
 */
int				fetch_int(char *str, int *i)
{
	printf("     +fetch_int\n");
	int			res;

	while (str[*i] && !ft_isdigit(str[*i]) && str[*i] ^ '-')
		*i += 1;
	res = ft_atoi(str + *i);
	while (str[*i] && ft_isdigit(str[*i]))
		*i += 1;
	printf("     -fetch_int\n");
	return (res);
}

/*
 * принимает строку, индекс в строке, кол-во интов в строке
 * аллочит массив интов
 * считывает инты в массив
 * возвращает указатель на массив интов
 * !> число интов в строке всегда парное
 * ?> не нужно проверять строку на наличие символов,
 * 		если она прошла через fetch_int()
 */
static int		*get_ints(char *s, int c, int *m)
{
	printf("    +get_ints\n");
	int			*res;
	int			i;

	res = (int*)malloc(sizeof(int) * *m);
	i = -1;
	while (++i < *m)
		res[i] = fetch_int(s, &c);
	*m /= 2;
	printf("    -get_ints\n");
	return (res);
}

/*
 * бисквит:
 *  реаллочит массив секторов на NumSectors + 1 (NumSectors - глобальный uint, = 0)
 *  считывает со строки пол, потолок
 *  считывает в цикле массив интов (тупо ВСЕ инты в строке без первых двух)
 *	npoints = кол-во вершин, npoints = половина кол-ва интов в строке
 * ? neighbours = соседние СЕКТОРа (signed char = 1 byte, -128->127)
 *	vertex = кол-во вершин в секторе, n(vertex) = arr / 2 + 1 (что б *замкнуть* сектор)
 * ----
 *  принимает массив секторов (или NULL, если пока пуст),
 *  строку, которую вернул гнл
 *  указатель на NumSectors
 *  указатель на массив вершин, полученый после всех итераций через vertex_init()
 *
 *  аллочит новый сектор
 *  считывает данные со строки
 *  реаллочит массив секторов, вставляя новый сектор в конец нового массива
 *  в процессе аллочит и фришит массив интов
 *
 *  возвращает указатель на новый массив
 *  или NULL если [давай по новой, Миша, всё ху@ня]
 */
t_sector		*sector_init(t_sector *arr, int *n_sectors, char *s, t_v2f *v)
{
	printf("  +sector_init\n");
	int			c;
	t_sector	*res;
	int			*num;
	int			m;

	c = 0;
	if ((*n_sectors += 1) < 0 && *num_ints(s, c, &m) % 2)
		return (NULL);
	res = (t_sector*)malloc(sizeof(t_sector) * *n_sectors);
	copy_arr(res, arr, *n_sectors - 1);
	res[*n_sectors - 1].floor = fetch_int(s, &c);
	res[*n_sectors - 1].ceil = fetch_int(s, &c);
	num = get_ints(s, c, num_ints(s, c, &m));
	res[*n_sectors - 1].npoints = m;
	res[*n_sectors - 1].neighbours = (char*)malloc(sizeof(char) * m);
	res[*n_sectors - 1].vertex = (t_v2f*)malloc(sizeof(t_v2f) * (m + 1));
	c = -1;
	while (++c < m)
	{
		printf(">> %d -- %d\n", *n_sectors, num[c]);
		res[*n_sectors - 1].vertex[c + 1] = v[num[c]];
		printf("x-x segf\n");
		res[*n_sectors - 1].neighbours[c] = num[m + c];
	}
	res[*n_sectors - 1].vertex[0] = res[*n_sectors - 1].vertex[m];
	free(num);
	printf("  -sector_init\n");
	return (res);
}
