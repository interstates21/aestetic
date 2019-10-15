#include "../includes/doom_nukem.h"

void	draw_health(t_data *d)
{
	static char buf[100] = "Health: ";

	ft_strcpy(buf + 8, ft_itoa_static(d->player.health));
	draw_string(d, (t_font){buf, 50, 50, 0xffffff, 2});
}

void	draw_ammo(t_data *d, t_weapon_type weapon_type)
{
	static char buf[100] = "QWERTYUIOPASDFGHJKLZXCVBNM :;.,?!";

	ft_strcpy(buf + 6, ft_itoa_static(weapon_type.current_ammo));
	ft_strcpy(buf + ft_strlen(buf), " / ");
	ft_strcpy(buf + ft_strlen(buf), ft_itoa_static(MAX_BULLETS));
	draw_string(d, (t_font){buf, 50, 80, 0xffffff, 2});
}

void	draw_fuel(t_data *d)
{
	static char buf[100] = "Fuel: ";

	ft_strcpy(buf + 6, ft_itoa_static(d->player.is_flying));
	draw_string(d, (t_font){buf, 50, 110, 0xffffff, 2});
}
