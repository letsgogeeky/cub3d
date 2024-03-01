#include "../../include/cube.h"

void	fill_var_map(int flag, char *ptr, t_map *m) // do the following spaces (if existing) need to be trimmed?
{
	if (flag == 1)
		m->north_texture->path = ft_strdup(ptr);
	else if (flag == 2)
		m->south_texture->path = ft_strdup(ptr);
	else if (flag == 3)
		m->west_texture->path = ft_strdup(ptr);
	else if (flag == 4)
		m->east_texture->path = ft_strdup(ptr);
	else if (flag == 5)
		m->floor_color->str_color = ft_strdup(ptr);
	else if (flag == 6)
		m->ceiling_color->str_color = ft_strdup(ptr);

}

void	set_var_map(t_map *m, char *ptr)
{
	int	i;
	int	flag;

	flag = 0;
	if (ft_strncmp(ptr, "NO ", 3) == 0)
		flag = 1;
	else if (ft_strncmp(ptr, "SO ", 3) == 0)
		flag = 2;
	else if (ft_strncmp(ptr, "WE ", 3) == 0)
		flag = 3;
	else if (ft_strncmp(ptr, "EA ", 3) == 0)
		flag = 4;
	else if (ft_strncmp(ptr, "F ", 2) == 0)
		flag = 5;
	else if (ft_strncmp(ptr, "C ", 2) == 0)
		flag = 6;
	if (flag == 0)
		return ;
	if (flag == 5 || flag == 6)
		i = 1;
	else
		i = 2;
	while (ptr[i] == ' ')
		i++;
	ptr = &ptr[i];
	fill_var_map(flag, ptr, m);
}



char *parse_walls(int fd, t_map *m)
{
	char	*tmp;
	char	*ptr;
	int		i;

	tmp = get_next_line(fd);
	ptr = NULL;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp[i] == ' ')
			i++;
		ptr = &tmp[i];
		if (find_start_map(ptr) == 0)
			break;
		set_var_map(m, ptr);
		free(tmp);
		tmp = get_next_line(fd);
	}
	return (tmp);
}
