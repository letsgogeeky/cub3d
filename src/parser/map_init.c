#include "../../include/cube.h"

void	set_char(int i, char *tmp, int max_length, t_map *m)
{
	int			j;
	int			len;

	j = 0;
	len = ft_strlen(tmp);
	while (j < len)
	{
		m->map[i][j] = tmp[j];
		j++;
	}
	while (j < max_length)
	{
		m->map[i][j] = ' ';
		j++;
	}
}

int	fill_map(t_map *m, int fd, int rows, int max_length)
{
	int		i;
	int		cnt;
	char	*tmp;

	i = 0;
	cnt = 0;
	m->map = ft_calloc((rows + 1), sizeof(char));
	if (m->map == NULL)
		return (1);
	tmp = get_next_line(fd);
	while (tmp != NULL && find_start_map(tmp) != 0)
		tmp = get_next_line(fd);
	while (i < rows && tmp != NULL)
	{
		m->map[i] = ft_calloc((max_length + 1), sizeof(char));
		if (m->map[i] == NULL)
		{
			while (--i >= 0)
				free(m->map[i]);
			return (free(m->map), m->map = NULL, 1);
		}
		set_char(i, tmp, max_length, m);
		free(tmp);
		cnt++;
		i++;
		tmp = get_next_line(fd);
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
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	fd = open(argv, O_RDONLY);
	if (fill_map(m, fd, rows, max_length) != 0)
		return (1);
	close(fd);
	test_parsing(m, rows);
	return (0);
}

t_map	*parse(int fd, char *argv)
{
	t_map	*m;
	char	*tmp;

	m = ft_calloc(1, sizeof(t_map));
	tmp = NULL;
	if (zero_map_struct(m) != 0)
		return (ft_prerr("struct init didnt work", NULL), NULL);
	tmp = parse_walls(fd, m); //map starts at tmp if everything worked right
	if (check_all_arg(m) != 0)
		return(free_map_struct(m), ft_prerr("invalid map", NULL), NULL);
	if (parse_map(fd, m, tmp, argv) != 0)
		return(free_map_struct(m), ft_prerr("parsing of map failed", NULL), NULL);
	return (m);
}

int main(int ac, char **argv)
{
	int fd;

	if (ac == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (ft_prerr("invalid file descriptor", NULL), 1);
		if (parse(fd, argv[1]) == NULL)
			return (ft_prerr("parsing failed", NULL), 1);
	}
	else
		return (ft_prerr("wrong amount of arguments", NULL), 1);
	return (0);
}
