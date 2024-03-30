#include "cube.h"

int	check_chars(char *ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i] && ptr[i] != '\0')
	{
		if (ptr[i] == '\n'|| ptr[i] == '\t' || ptr[i] == ' ')
			i++;
		else
			return (1);
	}
	return (0);
}

int	txt_color_flag_factory(char *ptr)
{
	if (ft_strncmp(ptr, "NO ", 3) == 0)
		return (1);
	else if (ft_strncmp(ptr, "SO ", 3) == 0)
		return (2);
	else if (ft_strncmp(ptr, "WE ", 3) == 0)
		return (3);
	else if (ft_strncmp(ptr, "EA ", 3) == 0)
		return (4);
	else if (ft_strncmp(ptr, "DD ", 3) == 0)
		return (5);
	else if (ft_strncmp(ptr, "F ", 2) == 0)
		return (6);
	else if (ft_strncmp(ptr, "C ", 2) == 0)
		return (7);
	else if (check_chars(ptr) == 0)
		return (8);
	return (0);
}

int	set_var_map(t_map *m, char *ptr)
{
	int	i;
	int	flag;

	flag = txt_color_flag_factory(ptr);
	if (flag == 0)
		return (1);
	i = 2;
	if (flag == 6 || flag == 7)
		i = 1;
	if (flag == 8)
		return (0);
	while (ptr[i] == ' ')
		i++;
	ptr = &ptr[i];
	if (fill_var_map(flag, ptr, m) != 0)
		return (2);
	return (0);
}

int	fill_color_struct(t_color *c)
{
	char	**arr;

	arr = ft_split(c->str_color, ',');
	if (arr == NULL || str_arr_len(arr) != 3)
		return (1);
	c->red = ft_atoi(arr[0]);
	c->green = ft_atoi(arr[1]);
	c->blue = ft_atoi(arr[2]);
	if (check_atoi_zero(c->red, arr[0]) != 0 || \
		check_atoi_zero(c->green, arr[1]) != 0 || \
		check_atoi_zero(c->blue, arr[2]) != 0)
		return (1);
	if (c->red < 0 || c->red > 255 || c->green < 0 || \
		c->green > 255 || c->blue < 0 || c->blue > 255)
		return (1);
	c->hex_color_rgb = colorcode(c->red, c->green, c->blue, 0xFF);
	return (0);
}

void	adjust_wall_path(t_map *m)
{
	check_n_change_c(m->north_texture->path);
	check_n_change_c(m->south_texture->path);
	check_n_change_c(m->west_texture->path);
	check_n_change_c(m->east_texture->path);
	check_n_change_c(m->door_texture->path);
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
		printf("tmp -%s-\n", tmp);
		if (set_var_map(m, ptr) != 0)
		{
			printf("hier\n");
			return (NULL);
		}
		free(tmp);
		tmp = get_next_line(fd);
	}
	adjust_wall_path(m);
	load_textures(m);
	if (fill_color_struct(m->ceiling_color) != 0 || \
		fill_color_struct(m->floor_color) != 0 || \
		check_textures(m) != 0)
		return (NULL);
	return (tmp);
}
