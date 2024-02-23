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
		if (!is_a_wall(line[i]) && line[i] != ' ')
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

int	largest_of_three(int a, int b, int c)
{
	if (a > b)
	{
		if (a > c)
			return (a);
		return (c);
	}
	if (b > c)
		return (b);
	return (c);
}
bool	valid_from_back(char *line, char *prev, char *next, char ignore)
{
	int	i;
	int	prev_i;
	int	next_i;
	int	largest;

	i = index_of_last_nonignore(line, ignore);
	prev_i = index_of_last_nonignore(prev, ignore);
	next_i = index_of_last_nonignore(next, ignore);
	largest = largest_of_three(i, prev_i, next_i);
	while (line[i] && i >= largest)
	{
		if (!is_a_wall(line[i]))
			return (false);
		i--;
	}
	return (true);
}
bool	valid_from_front(char *line, char *prev, char *next, char ignore)
{
	int	i;
	int	prev_i;
	int	next_i;
	int	largest;

	i = index_of_first_nonignore(line, ignore);
	prev_i = index_of_first_nonignore(prev, ignore);
	next_i = index_of_first_nonignore(next, ignore);
	largest = largest_of_three(i, prev_i, next_i);
	while (line[i] && i <= largest)
	{
		if (!is_a_wall(line[i]))
			return (false);
		if (!is_a_wall(line[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	valid_with_surrounding(char *line, char *prev, char *next, char ignore)
{
	if (!valid_from_front(line, prev, next, ignore))
		return (false);
	if (!valid_from_back(line, prev, next, ignore))
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
	if (!all_ones(map->map[0], ' ') || !all_ones(map->map[rows_count - 1], ' '))
		return (0);
	rows_count -= 2;
	while (rows_count > 0)
	{
		if (!surrounded_by_wall(map->map[rows_count] , ' '))
			return (0);
		if (!valid_with_surrounding(map->map[rows_count], map->map[rows_count - 1], map->map[rows_count + 1], ' '))
		{
			ft_printf("invalid with surrounding\n");
			return (0);
		}
		rows_count--;
	}
	return (1);
}
