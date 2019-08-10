#include "alt.h"

bool	    check_bound(t_scene *scene)
{
	int x;
	int y;

    x = 0;
	y = 0;
	while (y < scene->map_height)
	{
		if (scene->map[y][0] == '0' || scene->map[y][scene->map_width - 1] == '0')
			return (false);
		y++;
	}
	while (x < scene->map_width)
	{
		if (scene->map[0][x] == '0' || scene->map[scene->map_height - 1][x] == '0')
			return (false);
		x++;
	}
	return (true);
}

static	char    *parse_line(int fd, int map_width)
{
	char	*line;
	char	*ret;
	int		i;

	i = 0;

	if (!(ret = (char*)malloc(sizeof(char) * map_width + 1)))
		return (NULL);
	if (get_next_line(fd, &line) < 0)
		return (NULL);
	while (i < map_width)
	{
		ret[i] = line[i];
		i++;
	}
    ret[i] = '\0';
    if (line)
	    free(line);
	return (ret);
}

void        parse_map(int fd, t_scene *scene)
{
    int     i;

    i = 0;
    if (!(scene->map = (char**)malloc(sizeof(char*) * scene->map_height + 1)))
		print_err("Parse malloc failed.");
	while (i < scene->map_height)
	{
		if (!(scene->map[i] = parse_line(fd, scene->map_width)))
			print_err("Parse line failed.");
		i++;
	}
	scene->map[i] = NULL;
	if (!check_bound(scene))
		print_err("Invalid map: empty borders");
}

void        count_line(char *line,  int *len)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if ((line[i] < '0' || line[i] > '9'))
            print_err("Wrong symbol in the map.");
		i++;
	}
	*len = i;
    if (line)
        free(line);
}

void		count_map_size(int fd, t_scene *scene)
{
	char	*line;
    int  map_width;
    int  map_height;
    int  checker;

    map_width = 0;
    map_height = 0;
	while (get_next_line(fd, &line) > 0)
	{
        count_line(line, &map_width);
		if (map_height == 0)
			checker = map_width;
		else if (checker != map_width)
            print_err("Wrong map width");
		map_height++;
	}
	if (map_width < 3 || map_height < 3)
		print_err("The map must be larger than 3x3");
    scene->map_width = map_width;
    scene->map_height = map_height;
}



void		parse_manager(t_scene *scene, char *file)
{
    int fd;

    scene->map_width = 0;
    scene->map_height = 0;
	fd = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		print_err("Opening file for count falied.");
    count_map_size(fd, scene);
	close(fd);
    if ((fd = open(file, O_RDONLY)) == -1)
		print_err("Opening file for parsing falied.");
    parse_map(fd, scene);
    close(fd);
}

