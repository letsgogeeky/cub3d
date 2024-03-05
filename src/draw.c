# include "cube.h"

void	fill_block(t_game *game, int block_size, int x, int y)
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
			mlx_put_pixel(game->graphics->image, x, y, 0xFF0000FF);
			x++;
		}
		x = tmp_x;
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
			mlx_put_pixel(game->graphics->image, x, y, 0xFF0000FF);
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
		while (x < block_size * game->map->cols)
		{
			mlx_put_pixel(game->graphics->image, x, y, 0xFF0000FF);
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

	w = game->graphics->mlx->width;
	h = game->graphics->mlx->width;
	block_size = h / game->map->rows;
	printf("BLOCKSIZE1: %i\n", block_size);
	x = 0;
	y = 0;
	i = 0;
	j = 0;
	if (w / game->map->cols < block_size)
		block_size = w / game->map->cols;
	printf("BLOCKSIZE2: %i\n", block_size);
	draw_vert(game, block_size);
	draw_hor(game, block_size);
	while (game->map->map[i] != NULL)
	{
	printf("test\n");
		while (game->map->map[i][j] != '\0')
		{
			write(1, &game->map->map[i][j], 1);
			if (game->map->map[i][j] == 1)
			{
				fill_block(game, block_size, x, y);
			}
			x = x + block_size;
			j++;
		}
		write(1, "\n", 1);
		x = 0;
		i++;
		y = y + block_size;
	}
}
