#include "../../include/cube.h"

void	fill_var_map(int flag, char *ptr, t_map *m) // do the following spaces (if existing) need to be trimmed?
{
	if (flag == 1)
	{
		m->north_texture->path = ft_strdup(ptr);
		// printf("fillvarmap north %s\n", m->north_texture->path);
	}
	else if (flag == 2)
	{
		m->south_texture->path = ft_strdup(ptr);
		// printf("fillvarmap south %s\n", m->south_texture->path);
	}
	else if (flag == 3)
	{
		m->west_texture->path = ft_strdup(ptr);
		// printf("fillvarmap west %s\n", m->west_texture->path);
	}
	else if (flag == 4)
	{
		m->east_texture->path = ft_strdup(ptr);
		// printf("fillvarmap east %s\n", m->east_texture->path);
	}
	else if (flag == 5)
	{
		m->floor_color->str_color = ft_strdup(ptr);
		// printf("fillvarmap floor %s\n", m->floor_color->str_color);
	}
	else if (flag == 6)
	{
		m->ceiling_color->str_color = ft_strdup(ptr);
		// printf("fillvarmap ceiling %s\n", m->ceiling_color->str_color);
	}
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
	// printf("Flag:%i i:%i\n", flag, i);
	while (ptr[i] == ' ')
		i++;
	//printf("Flag:%i i:%i\n", flag, i);
	ptr = &ptr[i];
	fill_var_map(flag, ptr, m);
}

void	free_walls(t_map *m)
{
	if (m->north_texture != NULL)
		free(m->north_texture->path);
	if (m->south_texture != NULL)
		free(m->south_texture->path);
	if (m->west_texture != NULL)
		free(m->west_texture->path);
	if (m->east_texture != NULL)
		free(m->east_texture->path);
	if (m->floor_color != NULL)
		free(m->floor_color->str_color);
	if (m->ceiling_color != NULL)
		free(m->ceiling_color->str_color);
	zero_map_struct(m);
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
		//printf("%s\n", tmp);
		// if (m->north_texture->path != NULL)
		// 	printf("North: %s\n", m->north_texture->path);
		// if (m->south_texture->path != NULL)
		// 	printf("South: %s\n", m->south_texture->path);
		// if (m->west_texture->path != NULL)
		// 	printf("West: %s\n", m->west_texture->path);
		// if (m->east_texture->path != NULL)
		// 	printf("East: %s\n", m->east_texture->path);
		// if (m->floor_color->str_color != NULL)
		// 	printf("Floor: %s\n", m->floor_color->str_color);
		// if (m->ceiling_color->str_color != NULL)
		// 	printf("Ceiling: %s\n", m->ceiling_color->str_color);
			//do i need to count here in any way?
	}
	test_wall(m);
	return (tmp);
}
