#include "../includes/doom_nukem.h"

void	invoke_msg(t_data *d, char *msg)
{
	if (ft_strlen(msg) > 99)
		return ((void)printf("msg is too long\n"));
	ft_strcpy(d->msg, msg);
	d->msg_start = SDL_GetTicks();
}
