/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:57:14 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/23 15:57:15 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void draw_element(t_ed *e, t_font *f, int n, char *word)
{
	char 	*tmp;

	tmp = ft_itoa(n);
	f->y += 20;
	f->str = ft_strjoin(word, tmp);
	draw_string(e, *f);
	free(f->str);
	free(tmp);
}

static void	draw_background(t_ed *e, int n, int x, int y)
{
	int 	i;
	int 	j;

	n *= 20;
	i = -1;
	while (++i < 205 && (j = -1))
		while (++j < n)
			sdl_put_pix(&e->pixels, i + x, j + y, 0x111111);
}

static void	draw_nothing(t_ed *e, t_font f)
{
	draw_background(e, 1, f.x - 5, f.y + 15);
	f.y += 20;
	f.col = 0xffaaaa;
	f.str = "Sector: not selected.";
	draw_string(e, f);
}


static void	draw_sectinfo(t_ed *e, t_font f, int n)
{
	f.col = 0xffa0fa;
	draw_background(e, 11, f.x - 5, f.y + 15);
	draw_element(e, &f, n, "Sector: ");
	f.x += 15;
	draw_element(e, &f, e->seclist[n].slope[H_FLOOR], "Slope: ");
	draw_element(e, &f, e->seclist[n].slope_rot[H_FLOOR], "Slope ang: ");
	draw_element(e, &f, e->seclist[n].height[H_FLOOR], "FLOOR: ");
	draw_element(e, &f, e->seclist[n].height[H_CEIL], "CEIL: ");
	draw_element(e, &f, e->seclist[n].tex[T_FLOOR], "FLOOR tex: ");
	draw_element(e, &f, e->seclist[n].tex[T_WALL], "WALL tex: ");
	draw_element(e, &f, e->seclist[n].tex[T_CEIL], "CEIL tex: ");
	draw_element(e, &f, e->seclist[n].is_dmg, "danger: ");
	draw_element(e, &f, e->seclist[n].is_elev, "elevator: ");
	draw_element(e, &f, e->seclist[n].is_finish, "exit: ");
}

void		draw_info(t_ed *e)
{
	t_font	tmp;

	tmp.x = ED_W - 200;
	tmp.y = 50;
	e->selection.sector == -1 ? draw_nothing(e, tmp)
	: draw_sectinfo(e, tmp, e->selection.sector);
}
