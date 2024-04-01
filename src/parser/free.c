#include "../../include/cube.h"

void	free_s_texture(t_texture *t)
{
	if (t != NULL)
		free(t);
	t = NULL;
}

void	free_string(char *str)
{
	if (str != NULL)
		free(str);
	str = NULL;
}

void	free_color(t_color *c)
{
	if (c != NULL)
		free(c);
	c = NULL;
}

void	free_walls(t_map *m)
{
	free_string(m->north_texture->path);
	free_string(m->south_texture->path);
	free_string(m->west_texture->path);
	free_string(m->east_texture->path);
	free_string(m->floor_color->str_color);
	free_string(m->ceiling_color->str_color);
}

void	free_map_struct(t_map *m)
{
	int	i;

	i = 0;
	free_walls(m);
	free_s_texture(m->north_texture);
	free_s_texture(m->south_texture);
	free_s_texture(m->west_texture);
	free_s_texture(m->east_texture);
	free_s_texture(m->door_texture);
	free_color(m->ceiling_color);
	free_color(m->floor_color);
	if (m->map != NULL)
	{
		while (m->map[i] != NULL)
		{
			free(m->map[i]);
			m->map[i++] = NULL;
		}
		free(m->map);
		m->map = NULL;
	}
	free(m->doors);
	free(m);
	m = NULL;
}
