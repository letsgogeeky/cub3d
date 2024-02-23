#include "cube.h"

bool	is_a_wall(char c)
{
	return (c == '1');
}

bool	all_ones(char *line, char ignore)
{
	int	i;
	int	to;

	to = ft_strlen(line) - 1;
	i = 0;
	while (line[i] == ignore)
		i++;
	while (line[to] == ignore)
		to--;
	while (line[i] && i <= to)
	{
		if (!is_a_wall(line[i]))
			return (false);
		i++;
	}
	return (true);
}
int	index_of_first_nonignore(char *line, char ignore)
{
	int	i;

	i = 0;
	while (line[i] == ignore)
		i++;
	return (i);
}

int	index_of_last_nonignore(char *line, char ignore)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line[i] == ignore)
		i--;
	return (i);
}

bool	surrounded_by_wall(char *line, char ignore)
{
	int	i;

	i = index_of_first_nonignore(line, ignore);
	if (!is_a_wall(line[i]))
		return (false);
	i = index_of_last_nonignore(line, ignore);
	if (!is_a_wall(line[i]))
		return (false);
	return (true);
}

bool	valid_with_surrounding(char *line, char *prev, char *next, char ignore)
{
	int	i;
	(void)prev;
	(void)next;
	i = index_of_first_nonignore(line, ignore);
	if (!is_a_wall(line[i]))
		return (false);
	return (true);
}

int	validate(t_map *map)
{
	int	rows_count;
	int	cols_count;

	rows_count = str_arr_len(map->map);
	cols_count = ft_strlen(map->map[0]);
	ft_printf("rows: %d, cols: %d\n", rows_count, cols_count);
	if (rows_count < 3 || cols_count < 3)
		return (0);
	ft_printf("all_ones: %d\n", all_ones(map->map[0], ' '));
	ft_printf("all_ones: %d\n", all_ones(map->map[rows_count - 1], ' '));
	if (!all_ones(map->map[0], ' ') || !all_ones(map->map[rows_count - 1], ' '))
		return (0);
	while (rows_count--)
	{
		if (!surrounded_by_wall(map->map[rows_count] , ' '))
			return (0);
	}
	return (1);
}
