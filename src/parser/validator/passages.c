#include "cube.h"

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
	int		j;
	int		i;

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

bool	validate_bottom_top_passages(t_map *map)
{
	char	**grid;
	int		to;
	int		j;
	int		i;

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
