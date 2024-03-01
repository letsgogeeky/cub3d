#include "../../include/cube.h"

void	ft_prerr(char *str, char *argv)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != '\0')
		write(2, &str[i++], 1);
	if (argv != NULL)
	{
		i = 0;
		while (argv[i] != '\0')
			write(2, &str[i++], 1);
	}
	write(2, "\n", 1);
}

int	zero_map_struct(t_map *m)
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
	m->floor_color = ft_calloc(1, sizeof(t_color));
	if (m->floor_color == NULL)
		return (1);
	m->floor_color->str_color = NULL;
	m->ceiling_color = ft_calloc(1, sizeof(t_color));
	if (m->ceiling_color == NULL)
		return (1);
	m->ceiling_color->str_color = NULL;
	m->map = NULL;
	return (0);
}

void	free_map_struct(t_map *m)
{
	free_walls(m);
	free(m->north_texture);
	free(m->south_texture);
	free(m->west_texture);
	free(m->east_texture);
	free(m->ceiling_color);
	free(m->floor_color);
}

int	set_max_len(char *str, int max)
{
	int	i;

	i = ft_strlen(str);
	if (max < i)
		return (i);
	return (max);
}

int	find_start_map(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0)
	{
		if (str[len] == ' ' || str[len] == '1' || str[len] == '0')
			len--;
		else
			return(-1);
	}
	return(0);
}

int	check_all_arg(t_map *m)
{
	if (m->north_texture->path == NULL)
		return (1);
	if (m->south_texture->path == NULL)
		return (1);
	if (m->west_texture->path == NULL)
		return (1);
	if (m->east_texture->path == NULL)
		return (1);
	if (m->floor_color->str_color == NULL)
		return (1);
	if (m->ceiling_color->str_color == NULL)
		return (1);
	return (0);
}
