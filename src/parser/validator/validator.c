#include "validator.h"

bool	all_ones(char *line, char ignore)
{
	int	i;
	int	to;

	to = ft_strlen(line) - 1;
	i = 0;
	while (line[i] && line[i] == ignore)
		i++;
	while (to >= 0 && line[to] == ignore)
		to--;
	while (line[i] && i <= to)
	{
		if (line[i] != WALL && line[i] != ' ')
			return (false);
		i++;
	}
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

void	update_rows_cols_count(t_map *map)
{
	int		cols;
	int		rows;
	int		i;

	rows = str_arr_len(map->map);
	cols = ft_strlen(map->map[0]);
	map->cols = cols;
	i = rows - 1;
	while (i >= 0)
	{
		if (is_empty(map->map[i]))
			rows--;
		else
			break ;
		i--;
	}
	map->rows = rows;
}

int	validate(t_map *map)
{
	int		rows;
	int		cols;
	char	**grid;

	update_rows_cols_count(map);
	grid = map->map;
	rows = map->rows;
	cols = map->cols;
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
