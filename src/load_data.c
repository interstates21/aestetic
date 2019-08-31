
#include "../includes/alt.h"

//TODO: ща буит мясо

//TODO: gut_check()
//         ^^^ += (p|v|s_check) + scene_init()?
// страшна, вырубай

static int	check_f(char *s, int i)
{
	int 	point;

	point = -1;
	while (s[++i])
	{
		if (ft_isspace(s[i]) && (point = -1))
			continue ;
		if (!ft_isdigit(s[i]) && s[i] ^ '-' && s[i] ^ '.')
			return (0);
		if (s[i] == '-' && !ft_isspace(*(s + i - 1)))
			return (0);
		if (s[i] =='.' && (++point || !ft_isdigit(*(s + i - 1))
		|| !ft_isdigit(*(s + i + 1))))
			return (0);
	}
	return (1);
}

static int	check_i(char *s, int i)
{
	while (s[++i])
	{
		if (ft_isspace(s[i]))
			continue ;
		if (!ft_isdigit(s[i]) && s[i] ^ '-')
			return (0);
		if (s[i] == '-' && !ft_isspace(*(s + i - 1)))
			return (0);
	}
	return (1);
}

static int	gut_check(char *s, t_scene *g, t_v2f **v, int *n_v)
{
	if (!ft_strlen(s))
		return (1);
	if (s[0] == 'v')
	{
		if (ft_strncmp(s, "vertex", 6) || !check_f(s + 6, -1))
			return (0);
		return (init_vertices(s + 6, v, n_v));
	}
	else if (s[0] == 's')
	{
		if (ft_strncmp(s, "sector", 6) || !check_i(s + 6, -1))
			return (0);
		return ((g->sectors = sector_init(&g->sectors, &g->n_sectors, s + 6, *v))
		? 1 : 0);
	}
	else if (s[0] == 'p')
	{
		if (ft_strncmp(s, "player", 6) || !check_f(s + 6, -1))
			return (0);
		return (player_init(g, s + 6));
	}
	return (0);
}

static int	seq_check(int *i, char c)
{
	if (!c)
		return (1);
	if (c == 'v')
		*i = *i <= 1 ? 1 : 0;
	else if (c  == 's')
		*i = *i == 1 || *i == 2 ? 2 : 0;
	else if (c == 'p')
		*i = *i == 2 || *i == 3 ? 3 : 0;
	return (*i);
}

int 		load_data(char *fname, t_scene *scene)
{
	int 	fd;
	char	*line;
	t_v2f	*vert;
	int		n_vert;
	int 	stage;

	if ((fd = open(fname, O_RDONLY)) == -1)
		return (0);

	vert = NULL;
	n_vert = 0;
	stage = 0;
	while (get_next_line(fd, &line))
	{
		if (!seq_check(&stage, line[0])
		|| !gut_check(line, scene, &vert, &n_vert))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	free(vert);
	return (1);
}