#include "../includes/editor.h"

static void init_texure_picker_rect( SDL_Rect *SrcR, SDL_Rect *DestR, t_v2 pos, int size)
{
    SrcR->x = 0;
    SrcR->y = 0;
    SrcR->w = size;
    SrcR->h = size;
    DestR->x = ED_W - pos.x / 2 - size / 2;
    DestR->y = ED_H - pos.y / 2 - size / 2;
    DestR->w = size;
    DestR->h = size;
}

void render_picker(t_ed *ed, t_sdl *sdl) {
    SDL_Rect    SrcR;
    SDL_Rect    DestR;
    SDL_Texture *picker_tex;

     if (ed->texture_picker) {
        picker_tex = SDL_CreateTextureFromSurface(sdl->renderer, ed->texture_picker);
        init_texure_picker_rect(&SrcR, &DestR, new_v2(200, 200), SHAPE_SIZE);
        SDL_RenderCopy(sdl->renderer, picker_tex, &SrcR, &DestR);
    }
}

void render_monsters(t_ed *ed, t_sdl *sdl) {
    SDL_Rect    SrcR;
    SDL_Rect    DestR;
    SDL_Texture *tex;

    tex = SDL_CreateTextureFromSurface(sdl->renderer, ed->monster[0].acting[1][0]);
    init_texure_picker_rect(&SrcR, &DestR, new_v2(180, 500), 100);
    SDL_RenderCopy(sdl->renderer, tex, &SrcR, &DestR);
    tex = SDL_CreateTextureFromSurface(sdl->renderer, ed->monster[1].acting[0][0]);
    init_texure_picker_rect(&SrcR, &DestR, new_v2(400, 500), 100);
    SDL_RenderCopy(sdl->renderer, tex, &SrcR, &DestR);
}

void render_sprites(t_ed *ed, t_sdl *sdl) {
    SDL_Rect    SrcR;
    SDL_Rect    DestR;
    SDL_Texture *tex;
    int         i;
    int         offset;

    i       = 0;
    offset  = 0;
    while (i < ed->n_sprites) {
        tex = SDL_CreateTextureFromSurface(sdl->renderer, ed->sprites[i].texture);
        init_texure_picker_rect(&SrcR, &DestR, new_v2(600 - offset, 700), 30);
        SDL_RenderCopy(sdl->renderer, tex, &SrcR, &DestR);
        i++;
        offset += 80;
    }
}

int  pickers(t_ed *ed) {
    ed->selection.monster = -1;
	ed->selection.sprite = -1;
    if (ed->selection.sector == -1)
        return (0);
	if (picking_monster(ed->controller.mouse) == 1) {
		ft_putendl("Picking monster one");
		ed->selection.monster = 0;
		ed->selection.sprite = -1;
		return (1);
	}
	else if (picking_monster(ed->controller.mouse) == 2) {
		ft_putendl("Picking monster two");
		ed->selection.monster = 1;
		return (1);
	}
	else if (picking_sprite(ed->controller.mouse, ed->n_sprites) != -1) {
		ed->selection.sprite = picking_sprite(ed->controller.mouse, ed->n_sprites);
		ft_putstr("Picking sprite ");
		ft_putnbr(ed->selection.sprite);
		ft_putchar('\n');
		ed->selection.monster = -1;
		return (1);
	}
    return (0);
}