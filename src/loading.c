#include "../includes/doom_nukem.h"

static int	get_col(int p, int s)
{
	if (s <= p)
		return (0x00aa00);
	return (0x333333);
}

static void	draw_bar(t_data *d, int p)
{
	int		start;
	int 	end;
	int 	i;
	int 	j;
	int		col;

	ft_memset(d->sdl.screen->pixels, 0,
	d->sdl.screen->pitch * d->sdl.screen->h);
	start = (WIDTH >> 1) - 50;
	end = start + 100;
	i = start - 1;
	while (++i < end && (j = -1))
		while (++j < 5)
		{
			col = get_col(p, i - start);
			putpixel(d, i, j + (HEIGHT >> 1), col);
		}
}

void 		loading(t_data *d)
{
	int		status;
	int		i;
	char	*str;
	char	*tmp;

	status = 0;
	while (status <= 100)
	{
		str = ft_strdup("LOADING");
		i = -1;
		while (++i <= status % 3)
		{
			tmp = str;
			str = ft_strjoin(str, ".");
			free(tmp);
		}
		draw_bar(d, status);
		draw_string(d, (t_font){ str, (WIDTH >> 1) - 56, (HEIGHT >> 1) - 42, 0xaaaaaa, 2 });
		free(str);
		status += 4;
		SDL_UpdateWindowSurface(d->sdl.win);
		SDL_Delay(200);
	}
}