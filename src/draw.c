# include "cube.h"

void	fill_block(t_game *game, int block_size, int x, int y, int color)
{
	int	tmp_x;
	// int	cnt_y;
	int	x_max;
	int	y_max;

	tmp_x = x;
	// cnt_y = y;
	x_max = x + block_size;
	y_max = y + block_size;
	while (y < y_max)
	{
		while (x < x_max)
		{
			mlx_put_pixel(game->image, x, y, color);
			x++;
		}
		x = tmp_x;
		y++;
	}
}

void	draw_vert(t_game *game, int block_size)
{
	int	y;
	int	x;
	int	cnt;

	y = 0;
	x = 0;
	cnt = 0;
	while (cnt <= game->map->cols)
	{
		while (y < block_size * game->map->rows)
		{
			mlx_put_pixel(game->image, x, y, 0x000000FF);
			y++;
		}
		y = 0;
		x = x + block_size;
		cnt++;
	}
}

void	draw_hor(t_game *game, int block_size)
{
	int	y;
	int	x;
	int	cnt;

	y = 0;
	x = 0;
	cnt = 0;
	while (cnt <= game->map->rows)
	{
		while (x < block_size * (game->map->cols)) // why one more column then chars
		{
			mlx_put_pixel(game->image, x, y, 0x000000FF);
			x++;
		}
		x = 0;
		y = y + block_size;
		cnt++;
	}
}

void	draw_block(t_game *game)
{
	int	w;
	int	h;
	int	block_size;
	int	x;
	int	y;
	int	i;
	int	j;

	w = game->mlx->width;
	h = game->mlx->width;
	block_size = h / game->map->rows;
	x = 0;
	y = 0;
	i = 0;
	j = 0;
	if (w / (game->map->cols) < block_size)
		block_size = w / (game->map->cols);
	draw_vert(game, block_size);
	draw_hor(game, block_size);
	while (i < game->map->rows)
	{
		while (game->map->map[i][j] != '\0')
		{
			if (game->map->map[i][j] == '1')
				fill_block(game, block_size, x, y, 0x000000FF);
			else if (ft_strchr("NSEW", game->map->map[i][j]) != NULL)
				fill_block(game, block_size, x, y, 0x00FFFFFF);
			x = x + block_size;
			j++;
		}
		j = 0;
		x = 0;
		i++;
		y = y + block_size;
	}
}
