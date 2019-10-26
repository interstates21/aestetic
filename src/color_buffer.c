/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:18:24 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/26 21:28:14 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	set_find_alpha(double *sl_x, double *sl_y)
{
	short	x;

	x = -1;
	while (++x < WIDTH)
		sl_x[x] = fabs(x - WIDTH * 0.5) / (WIDTH * 0.5);
	alpha_y(sl_y);
}

double	find_alpha(short x, short y, uint32_t which_ret)
{
	static bool		set;
	static double	sl_x[WIDTH];
	static double	sl_y[HEIGHT];

	if (!set)
	{
		set_find_alpha(&sl_x[0], &sl_y[0]);
		set = true;
	}
	if (which_ret == GREEN_BLAST)
		return ((sl_x[x] + sl_y[y]) * 0.5);
	if (sl_x[x] > sl_y[y])
		return (sl_x[x]);
	return (sl_y[y]);
}

void	color_screen(t_args_multi_colo_buf *data)
{
	int			x;
	int			y;
	uint32_t	colo;
	uint8_t		tmp;

	x = data->start_x;
	while (++x < data->max_x)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			if (data->d->color_buf.colo == GREEN_BLAST)
				tmp = (uint8_t)((1 - find_alpha(x, y,
					data->d->color_buf.colo)) * data->d->color_buf.value);
			else
				tmp = (uint8_t)((find_alpha(x, y, data->d->color_buf.colo)) *
						data->d->color_buf.value);
			colo = data->d->color_buf.colo + (tmp << 24);
			pixel_put(data->d, new_v3(x, y, 0),
					alpha(pixel_pls(data->d->sdl.screen, x, y, 2), colo), 0);
		}
	}
}

void	color_wl(t_data *d, t_args_multi_colo_buf *col, short i, pthread_t *sp)
{
	while (i < MAX_THREADS)
	{
		col[i].d = d;
		if (i == 0)
			col[i].start_x = -1;
		else
			col[i].start_x = col[i - 1].max_x - 1;
		col[i].max_x = WIDTH / MAX_THREADS * (i + 1);
		pthread_create(&sp[i], NULL, (void *)color_screen, &col[i]);
		i++;
	}
	while (--i >= 0)
		pthread_join(sp[i], NULL);
}

void	color_buffer(t_data *d)
{
	pthread_t				sp[MAX_THREADS];
	t_args_multi_colo_buf	col[MAX_THREADS];
	short					i;

	if (!d->color_buf.value)
		return ;
	i = 0;
	color_wl(d, col, i, sp);
	if (col->d->color_buf.colo == GREEN_BLAST)
		col->d->color_buf.value -= 6;
	else
		col->d->color_buf.value -= 1;
	col->d->color_buf.value = MAX(0, col->d->color_buf.value);
}
