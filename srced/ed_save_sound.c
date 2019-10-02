/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_write_sound.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:55:56 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/07/09 22:20:50 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

#define MAX_SIZE_FOR_SOUND 5000000

int		write_sound2(int f, char *path)
{
	uint8_t		*file;
	int			read_ret;
	int			fd;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (printf("Couldn't open sound file: %s\n", path));
	if (!(file = malloc(MAX_SIZE_FOR_SOUND)))
		return (printf("Malloc for sound failed\n"));
	read_ret = read(fd, file, MAX_SIZE_FOR_SOUND);
	if (read_ret < 0)
		return (printf("Error reading file: %s\n", path));
	if (read_ret >= MAX_SIZE_FOR_SOUND)
		return (printf("Error file too big:%s\n", path));
	if (write(f, &read_ret, sizeof(read_ret)) < 0)
		return (printf("Failed to write sound file\n"));
	if (write(f, file, read_ret) < 0)
		return (printf("Failed to write sound file\n"));
	close(fd);
	free(file);
	return (0);
}

int		write_sound(int f)
{
	if (write_sound2(f, "./sounds/music.wav") ||
			write_sound2(f, "./sounds/blaster.wav") ||
			write_sound2(f, "sounds/cryo_bal.wav") ||
			write_sound2(f, "sounds/m16.wav") ||
			write_sound2(f, "sounds/explosion.wav") ||
			write_sound2(f, "sounds/player_fell.wav") ||
			write_sound2(f, "sounds/player_got_hit.wav") ||
			write_sound2(f, "sounds/player_death.wav") ||
			write_sound2(f, "sounds/charg_agro.wav") ||
			write_sound2(f, "sounds/charg_damage.wav") ||
			write_sound2(f, "sounds/charg_death.wav") ||
			write_sound2(f, "sounds/mother_agro.wav") ||
			write_sound2(f, "sounds/mother_attack.wav") ||
			write_sound2(f, "sounds/mother_death.wav") ||
			write_sound2(f, "sounds/blaster_2.wav") ||
			write_sound2(f, "sounds/refill_ammo.wav") ||
			write_sound2(f, "sounds/health_up.wav") ||
			write_sound2(f, "sounds/door_open.wav") ||
			write_sound2(f, "sounds/door_close.wav") ||
			write_sound2(f, "sounds/the-pikachu-song.wav"))
		return (1);
	return (0);
}
