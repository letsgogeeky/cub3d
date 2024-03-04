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
	if (m->ceiling_color != NULL)
		free(m->ceiling_color);
	m->ceiling_color = NULL;
	if (m->floor_color != NULL)
		free(m->floor_color);
	m->floor_color = NULL;
	while (m->map[i] != NULL)
	{
		free(m->map[i]);
		m->map[i] = NULL;
		i++;
	}
	free(m->map);
	m->map = NULL;
	free(m);
	m = NULL;
}

void	free_map_struct2(t_map *m)
{
	free_walls(m);
	if (m->north_texture != NULL)
		free(m->north_texture);
	m->north_texture = NULL;
	if (m->south_texture != NULL)
		free(m->south_texture);
	m->south_texture = NULL;
	if (m->west_texture != NULL)
		free(m->west_texture);
	m->west_texture = NULL;
	if (m->east_texture != NULL)
		free(m->east_texture);
	m->east_texture = NULL;
	if (m->ceiling_color != NULL)
		free(m->ceiling_color);
	m->ceiling_color = NULL;
	if (m->floor_color != NULL)
		free(m->floor_color);
	m->floor_color = NULL;
	free(m);
	m = NULL;
}
