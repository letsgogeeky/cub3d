#include "../../include/cube.h"

void	set_char(int i, char *tmp, int max_length, t_map *m)
{
	int			j;
	int			len;

	j = 0;
	len = ft_strlen(tmp) - 1;
	while (j < len)
	{
		m->map[i][j] = tmp[j];
		j++;
	}
	if (tmp[j] != '\0' && (j < max_length))
	{
		if (tmp[j] == '\n')
			m->map[i][j] = ' ';
		else
			m->map[i][j] = tmp[j];
		j++;
	}
	while (j < max_length)
		m->map[i][j++] = ' ';
}

char	*get_line_free_tmp(char *tmp, int fd)
{
	free(tmp);
	return (get_next_line(fd));
}

int	fill_map(t_map *m, int fd, int rows, int max_length)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = get_next_line(fd);
	while (tmp != NULL && find_start_map(tmp) != 0)
		tmp = get_line_free_tmp(tmp, fd);
	while (++i < rows && tmp != NULL)
	{
		m->map[i] = ft_calloc((max_length + 1), sizeof(char));
		if (m->map[i] == NULL)
		{
			while (--i >= 0)
				free(m->map[i]);
			return (free(m->map), free(tmp), m->map = NULL, tmp = NULL, 1);
		}
		set_char(i, tmp, max_length, m);
		tmp = get_line_free_tmp(tmp, fd);
	}
	if (tmp == NULL && i != rows)
		return (1);
	return (0);
}

int	parse_map(int fd, t_map *m, char *tmp, char *argv)
{
	int		rows;
	int		max_length;

	rows = 0;
	max_length = 0;
	while (tmp != NULL)
	{
		rows++;
		max_length = set_max_len(tmp, max_length);
		tmp = get_line_free_tmp(tmp, fd);
	}
	close(fd);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (1);
	m->map = ft_calloc((rows + 1), sizeof(char *));
	if (m->map == NULL)
		return (close(fd), 1);
	if (fill_map(m, fd, rows, max_length) != 0)
		return (close(fd), 1);
	return (close(fd), 0);
}

t_map	*parse(t_map *m, int fd, char *argv)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	if (zero_map_struct(m) != 0)
		return (free_map_struct(m), ft_prerr(STRUCT_FAILED, NULL), NULL);
	tmp = parse_walls(fd, m);
	if (tmp == NULL)
		return (free_map_struct(m), ft_prerr(PARSING_MAP_FAILED, NULL), NULL);
	i = check_all_arg(m);
	if (i != 0)
	{
		while (tmp != NULL)
			tmp = get_line_free_tmp(tmp, fd);
		if (i == 1)
		{
			free_map_struct(m);
			return (close(fd), ft_prerr(INV_MAP, NULL), NULL);
		}
	}
	if (parse_map(fd, m, tmp, argv) != 0)
		return (free_map_struct(m), ft_prerr(PARSING_MAP_FAILED, NULL), NULL);
	return (m);
}
