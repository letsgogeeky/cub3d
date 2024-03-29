#include "validator.h"

bool	all_ones(char *line, bool allow_empty)
{
	int	i;
	int	to;

	to = ft_strlen(line) - 1;
	i = 0;
	while (line[i] && line[i] == EMPTY)
		i++;
	while (to >= 0 && line[to] == EMPTY)
		to--;
	while (line[i] && i <= to)
	{
		if (line[i] != WALL && line[i] != EMPTY)
			return (false);
		if (!allow_empty && line[i] == EMPTY)
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
			if (grid[i][j] != WALL && grid[i][j] != EMPTY && \
				grid[i][j] != SPACE && !ft_strchr("NSEWD", grid[i][j]))
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

bool	hit_wall_left(char **grid, int i, int j)
{
	while (j >= 1)
	{
		if (grid[i][j] == SPACE)
			return (false);
		if (grid[i][j] == WALL)
			return (true);
		j--;
	}
	return (false);
}

bool	hit_wall_right(char **grid, int i, int j, int cols)
{
	while (j < cols - 1)
	{
		if (grid[i][j] == SPACE)
			return (false);
		if (grid[i][j] == WALL)
			return (true);
		j++;
	}
	return (false);
}
bool	validate_top_bottom_passages(t_map *map)
{
	char	**grid;
	int		to;
	int	j;
	int	i;

	grid = map->map;
	if (all_ones(grid[0], false))
		return (true);
	i = 0;
	j = index_of_nonignore(grid[i], EMPTY, true);
	to = index_of_nonignore(grid[map->rows - 1], EMPTY, false);
	while (j < to)
	{
		while (grid[i][j] == EMPTY)
		{
			if (!hit_wall_right(grid, i, j, to) || !hit_wall_left(grid, i, j))
				return (false);
			i++;
			if (i >= map->rows || grid[i][j] == SPACE)
				return (false);
		}
		j++;
	}
	return (true);
}

bool validate_bottom_top_passages(t_map *map)
{
	char	**grid;
	int		to;
	int	j;
	int	i;

	grid = map->map;
	if (all_ones(grid[map->rows - 1], false))
		return (true);
	i = map->rows - 1;
	j = index_of_nonignore(grid[i], EMPTY, true);
	to = index_of_nonignore(grid[map->rows - 1], EMPTY, false);
	while (j < to)
	{
		while (grid[i][j] == EMPTY)
		{
			if (!hit_wall_right(grid, i, j, to) || !hit_wall_left(grid, i, j))
				return (false);
			i--;
			if (i <= 0 || grid[i][j] == SPACE)
				return (false);
		}
		j++;
	}
	return (true);
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
		return (printf("-> Failed on map minimum size requirements.\n"), 0);
	if (!all_ones(grid[0], true) || !all_ones(grid[rows - 1], true))
		return (printf("-> Failed on First / Last row checks\n"), 0);
	if (!validate_symbols(map))
		return (printf("-> Failed on Symbols checks\n"), 0);
	if (!validate_top_bottom_passages(map) || !validate_bottom_top_passages(map))
		return (printf("-> Failed on passages checks\n"), 0);
	rows -= 2;
	while (rows > 0)
	{
		if (!surrounded_by_wall(grid[rows] , EMPTY))
			return (printf("-> Failed on Walls Checks at row: %d\n", rows), 0);
		if (!valid_with_surrounding(grid[rows], grid[rows - 1], grid[rows + 1], EMPTY))
			return (printf("-> Failed on validating internal map content and boundaries at row: %d\n", rows), 0);
		rows--;
	}
	return (1);
}
