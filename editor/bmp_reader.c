/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:15:38 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/17 17:15:39 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	check_header(t_bmp *data, char *s, int *fd)
{
	reopen_fd(fd, s);
	if (read(*fd, &data->signature, 2) < 0 ||
		read(*fd, &data->size, 4) < 0 ||
		read(*fd, &data->useless, 4) < 0 ||
		read(*fd, &data->offset, 4) < 0 ||
		read(*fd, &data->header_size, 4) < 0 ||
		read(*fd, &data->width, 4) < 0 ||
		read(*fd, &data->height, 4) < 0 ||
		read(*fd, &data->planes, 2) < 0 ||
		read(*fd, &data->bpp, 2) < 0 ||
		data->signature[0] != 'B' ||
		data->signature[1] != 'M' ||
		data->width < 1 || data->height < 1 ||
		data->bpp ^ 32)
		print_err("bmp file is corrupted");
}

static void	buf_init(void **b, t_bmp *data, int fd)
{
	if (!(*b = (void*)malloc(data->size)))
		print_err("malloc failed");
	if ((read(fd, *b, data->size)) < 0)
		print_err("reading bmp failed");
}

void		read_bmp(SDL_Surface **s, char *p)
{
	int		k;
	t_bmp	data;
	void	*buf;
	int		fd;

	fd = -1;
	check_header(&data, p, &fd);
	if (!(*s = SDL_CreateRGBSurfaceWithFormat(0, data.width,
	data.height, 32, SDL_PIXELFORMAT_ABGR8888)))
		print_err("creating texture failed");
	reopen_fd(&fd, p);
	buf_init(&buf, &data, fd);
	k = 0;
	while (data.size > data.offset)
	{
		data.size -= data.width * 4;
		ft_memcpy(&((uint8_t*)(*s)->pixels)[k],
		&((uint8_t*)buf)[data.size], data.width * 4);
		k += data.width * 4;
	}
	free(buf);
	close(fd);
}

int			bmp_check(struct dirent *data)
{
	int		len;

	len = ft_strlen(data->d_name) - 4;
	return (data->d_type == DT_REG &&
	ft_strequ(&data->d_name[len], ".bmp"));
}
