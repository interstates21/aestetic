/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_bmp_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 18:43:57 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/26 18:44:01 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "bmp_reader.h"

int				get_bmp_header(t_bmp *bmp, char *path)
{
	int	fd;

	if ((fd = open(path, O_RDONLY)) != -1)
	{
		if (read(fd, &bmp->header.signature, 2) < 0 ||
			read(fd, &bmp->header.filesize, 4) < 0 ||
			read(fd, &bmp->header.unused, 4) < 0 ||
			read(fd, &bmp->header.data_offset, 4) < 0 ||
			read(fd, &bmp->header.sizeinfoheader, 4) < 0 ||
			read(fd, &bmp->header.width, 4) < 0 ||
			read(fd, &bmp->header.height, 4) < 0 ||
			read(fd, &bmp->header.planes, 2) < 0 ||
			read(fd, &bmp->header.bpp, 2) < 0)
			return (printf("Failed to read BMP header\n"));
		close(fd);
	}
	if (bmp->header.bpp != 32)
		return (printf("Not a 32 bits BMP, need ARGB8888 format bmp.\n"));
	if (bmp->header.width <= 0 || bmp->header.height <= 0)
		return (1);
	return ((bmp->header.signature[0] == 'B' &&
			bmp->header.signature[1] == 'M') ? 0 : 1);
}

SDL_Surface		*load_bmp(char *path)
{
	int			fd;
	t_bmp		bmp;
	SDL_Surface	*surface;
	void		*data;
	int			j;

	surface = NULL;
	if (!get_bmp_header(&bmp, path) && (fd = open(path, O_RDONLY)) != -1)
	{
		if (!(data = malloc(bmp.header.filesize)) ||
			((j = 0) != -1 && (read(fd, data, bmp.header.filesize) < 0)) ||
			!(surface = SDL_CreateRGBSurfaceWithFormat(0, bmp.header.width,
							bmp.header.height, 32, SDL_PIXELFORMAT_ARGB8888)))
			return (NULL);
		while (bmp.header.filesize > bmp.header.data_offset)
		{
			bmp.header.filesize -= bmp.header.width * 4;
			ft_memcpy(&((uint8_t*)surface->pixels)[j],
				&((uint8_t*)data)[bmp.header.filesize], bmp.header.width * 4);
			j += bmp.header.width * 4;
		}
		free(data);
		close(fd);
	}
	return (surface);
}
