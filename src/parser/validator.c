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

bool	validate_symbols(t_map *map)
{
	char	**grid;
	int		i;
	int		j;
	bool	has_player;

	grid = map->map;
	i = -1;
	has_player = false;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			if (grid[i][j] != '1' && grid[i][j] != '0' && \
				grid[i][j] != ' ' && !ft_strchr("NSEW", grid[i][j]))
				return (false);
			if (ft_strchr("NSEW", grid[i][j]))
			{
				if (has_player)
					return (false);
				has_player = true;
			}
		}
	}
	return (has_player);
}

int	validate(t_map *map)
{
	int		rows;
	int		cols;
	char	**grid;

	grid = map->map;
	rows = str_arr_len(grid);
	cols = ft_strlen(grid[0]);
	map->rows = rows;
	map->cols = cols;
	if (rows < 3 || cols < 3)
		return (0);
	if (!all_ones(grid[0], ' ') || !all_ones(grid[rows - 1], ' '))
		return (0);
	if (!validate_symbols(map))
		return (0);
	rows -= 2;
	while (rows > 0)
	{
		if (!surrounded_by_wall(grid[rows] , ' '))
			return (0);
		if (!valid_with_surrounding(grid[rows], grid[rows - 1], grid[rows + 1], ' '))
			return (0);
		rows--;
	}
	return (1);
}
