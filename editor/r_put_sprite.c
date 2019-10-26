#include "../includes/editor.h"

static t_mnst  new_monster(t_v2 pos, int n_sect, int type) {
    t_mnst m;

    m.pos = pos;
    m.n_sect = n_sect;
    m.type = type;
    return (m);
}

static t_sprt  new_sprite(t_v2 pos, int n_sect, int type) {
    t_sprt m;

    m.pos = pos;
    m.n_sect = n_sect;
    m.type = type;
    return (m);
}

void put_monster(t_ed *ed, int n_sect) {
    if (ed->selection.monster == -1)
        return ;
    if (ed->n_mns >= MAX_MONS) {
        ft_putendl("Sorry, too many monsters!");
        return ;
    }
    
    ed->monst[ed->n_mns] = new_monster(ed->controller.mouse, n_sect, ed->selection.monster);
    ed->n_mns++;
}

void put_sprite(t_ed *ed, int n_sect) {
    if (ed->selection.sprite == -1)
        return ;
    if (ed->n_sprt >= MAX_SPRT) {
        ft_putendl("Sorry, too many sprites!");
        return ;
    }
    
    ed->sprt[ed->n_sprt] = new_sprite(ed->controller.mouse, n_sect, ed->selection.sprite);
    ed->n_sprt++;
}