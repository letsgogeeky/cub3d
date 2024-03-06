#include "../../include/cube.h"

void	fill_var_map(int flag, char *ptr, t_map *m)
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
	i = 2;
	if (flag == 5 || flag == 6)
		i = 1;
	while (ptr[i] == ' ')
		i++;
	ptr = &ptr[i];
	fill_var_map(flag, ptr, m);
}

int	fill_color_struct(t_color *c)
{
	char	**arr;

	arr = ft_split(c->str_color, ',');
	c->red = ft_atoi(arr[0]);
	c->green = ft_atoi(arr[1]);
	c->blue = ft_atoi(arr[2]);
	if (c->red < 0 || c->red > 255 || c->green < 0 || \
		c->green > 255 || c->blue < 0 || c->blue > 255)
		return (ft_prerr(INV_MAP, NULL), 1);
	c->hex_color_rgb = colorcode(c->red, c->green, c->blue);
	return (0);
}

void	adjust_wall_path(t_map *m)
{
	check_n_change_c(m->north_texture->path);
	check_n_change_c(m->south_texture->path);
	check_n_change_c(m->west_texture->path);
	check_n_change_c(m->east_texture->path);
}

char	*parse_walls(int fd, t_map *m)
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
			break ;
		set_var_map(m, ptr);
		free(tmp);
		tmp = get_next_line(fd);
	}
	adjust_wall_path(m);
	if (fill_color_struct(m->ceiling_color) != 0 || \
		fill_color_struct(m->floor_color) != 0)
		return (0);
	return (tmp);
}
