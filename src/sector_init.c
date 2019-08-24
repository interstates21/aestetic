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

//TODO: copy_arr()
//TODO: fetch_int()
//TODO:    ^^^ *= get_ints()

//TODO: load_data()

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
t_sector		*sector_init(t_sector *arr, int *NumSectors, char *s, t_v2f *v)
{
	int			c;
	t_sector	*res;
	int 		*num;
	int 		m;
	int 		n;

	c = 0;
	*NumSectors += 1;
	res = (t_sector*)malloc(sizeof(t_sector) * *NumSectors);
	copy_arr(res, arr, *NumSectors - 1);
	res[*NumSectors - 1].floor = fetch_int(s, &c);
	res[*NumSectors - 1].ceil = fetch_int(s, &c);
	num = get_ints(s, c, &m);
	res[*NumSectors - 1].npoints = m;
	res[*NumSectors - 1].neighbours = (char*)malloc(sizeof(char) * m);
	res[*NumSectors - 1].vertex = (t_v2f*)malloc(sizeof(t_v2f) * (m + 1));
	n = -1;
	while (++n < m)
	{
		res[*NumSectors - 1].vertex[n + 1] = v[num[n]];
		res[*NumSectors - 1].neighbours[n] = num[m + n];
	}
	res[*NumSectors - 1].vertex[0] = res[*NumSectors - 1].vertex[m];
	free(num);
	return (res);
}
