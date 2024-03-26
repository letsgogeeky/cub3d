#include "../../include/cube.h"

void	check_n_change_c(char *str)
{
	int	i;
	int	len;

	i = 0;
	if (str == NULL)
		return ;
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
	char	*tmp;

	tmp = m->north_texture->path;
	if (access(tmp, F_OK) != 0 || access(tmp, R_OK) != 0)
		return (1);
	tmp = m->south_texture->path;
	if (access(tmp, F_OK) != 0 || access(tmp, R_OK) != 0)
		return (1);
	tmp = m->west_texture->path;
	if (access(tmp, F_OK) != 0 || access(tmp, R_OK) != 0)
		return (1);
	tmp = m->east_texture->path;
	if (access(tmp, F_OK) != 0 || access(tmp, R_OK) != 0)
		return (1);
	tmp = m->door_texture->path;
	if (!tmp)
		return (0);
	if (access(tmp, F_OK) != 0 || access(tmp, R_OK) != 0)
		return (1);
	return (0);
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
