#include "cube.h"

static int	allocate_textures(t_map *m)
{
	m->north_texture = ft_calloc(1, sizeof(t_texture));
	if (m->north_texture == NULL)
		return (1);
	m->north_texture->path = NULL;
	m->south_texture = ft_calloc(1, sizeof(t_texture));
	if (m->south_texture == NULL)
		return (1);
	m->south_texture->path = NULL;
	m->west_texture = ft_calloc(1, sizeof(t_texture));
	if (m->west_texture == NULL)
		return (1);
	m->west_texture->path = NULL;
	m->east_texture = ft_calloc(1, sizeof(t_texture));
	if (m->east_texture == NULL)
		return (1);
	m->east_texture->path = NULL;
	m->door_texture = ft_calloc(1, sizeof(t_texture));
	if (m->door_texture == NULL)
		return (1);
	m->door_texture->path = NULL;
	return (0);
}

static int	allocate_colors(t_map *m)
{
	m->floor_color = ft_calloc(1, sizeof(t_color));
	if (m->floor_color == NULL)
		return (1);
	m->floor_color->str_color = NULL;
	m->ceiling_color = ft_calloc(1, sizeof(t_color));
	if (m->ceiling_color == NULL)
		return (1);
	m->ceiling_color->str_color = NULL;
	return (0);
}

int	zero_map_struct(t_map *m)
{
	if (allocate_textures(m))
		return (1);
	if (allocate_colors(m))
		return (1);
	return (m->map = NULL, 0);
}

int	fill_var_map(int flag, char *ptr, t_map *m)
{
	if (flag == 1 && m->north_texture->path == NULL)
		m->north_texture->path = ft_strdup(ptr);
	else if (flag == 2 && m->south_texture->path == NULL)
		m->south_texture->path = ft_strdup(ptr);
	else if (flag == 3 && m->west_texture->path == NULL)
		m->west_texture->path = ft_strdup(ptr);
	else if (flag == 4 && m->east_texture->path == NULL)
		m->east_texture->path = ft_strdup(ptr);
	else if (flag == 5 && m->door_texture->path == NULL)
		m->door_texture->path = ft_strdup(ptr);
	else if (flag == 6 && m->floor_color->str_color == NULL)
		m->floor_color->str_color = ft_strdup(ptr);
	else if (flag == 7 && m->ceiling_color->str_color == NULL)
		m->ceiling_color->str_color = ft_strdup(ptr);
	else if(flag != 8)
		return (1);
	return (0);
}
