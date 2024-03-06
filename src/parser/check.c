#include "../../include/cube.h"

void	check_n_change_c(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '\n' || str[i] == ' ')
			str[i] = '\0';
		i++;
	}
}

int	check_end(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = len - 4;
	// printf("||||%s||||||\n", &str[i]);
	if (ft_strncmp(&str[i], ".cub", 4) != 0)
		return (ft_prerr(CUB_FORMAT, NULL), 1);
	return (0);
}

int	check_path(t_map *m)
{
	int a;
	int	b;
	int	c;
	int	d;

	a = open(m->north_texture->path, O_RDONLY);
	b = open(m->south_texture->path, O_RDONLY);
	c = open(m->west_texture->path, O_RDONLY);
	d = open(m->east_texture->path, O_RDONLY);
	// printf("%s\n", m->north_texture->path);
	// printf("%s\n", m->south_texture->path);
	// printf("%s\n", m->west_texture->path);
	// printf("%s\n", m->east_texture->path);
	// printf("A: %i, B: %i, C: %i, D: %i\n", a, b, c, d);
	if (a < 0 || b < 0 || c < 0 || d < 0)
		return (1);
	close(a);
	close(b);
	close(c);
	close(d);
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
	if (check_path(m) != 0)
		return (2);
	return (0);
}
