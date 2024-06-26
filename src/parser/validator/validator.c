#include "cube.h"

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

int	validate(t_map *m)
{
	int		r;
	int		c;
	char	**g;

	update_rows_cols_count(m);
	g = m->map;
	r = m->rows;
	c = m->cols;
	if (r < 3 || c < 3)
		return (printf("-> Failed on map minimum size requirements.\n"), 0);
	if (!all_ones(g[0], true) || !all_ones(g[r - 1], true))
		return (printf("-> Failed on First / Last row checks\n"), 0);
	if (!validate_symbols(m))
		return (printf("-> Failed on Symbols checks\n"), 0);
	if (!validate_top_bottom_passages(m) || !validate_bottom_top_passages(m))
		return (printf("-> Failed on passages checks\n"), 0);
	r -= 1;
	while (--r > 0)
	{
		if (!surrounded_by_wall(g[r], EMPTY))
			return (printf("-> Failed on Walls Checks at row: %d\n", r), 0);
		if (!valid_with_surrounding(g[r], g[r - 1], g[r + 1], EMPTY))
			return (printf("-> Failed on map boundaries at row: %d\n", r), 0);
	}
	return (1);
}
