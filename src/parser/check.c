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

int	check_atoi_zero(int color, char *arr)
{
	if (color == 0)
	{
		if (ft_strchr(arr, '0') == NULL)
			return (1);
	}
	return (0);
}

int	check_end(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = len - 4;
	if (ft_strncmp(&str[i], ".cub", 4) != 0)
		return (ft_prerr(CUB_FORMAT, NULL), 1);
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
	return (0);
}

int	check_chars(char *ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i] && ptr[i] != '\0')
	{
		if (ft_isempty(ptr[i]) == 1)
			i++;
		else
			return (1);
	}
	return (0);
}
