# include "cube.h"

void	fill_block(t_game *game, int block_size)
{

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

	w = game->graphics->mlx->width;
	h = game->graphics->mlx->width;
	block_size = h / game->map->rows;
	printf("BLOCKSIZE1: %i\n", block_size);
	if (w / game->map->cols < block_size)
		block_size = w / game->map->cols;
	printf("BLOCKSIZE2: %i\n", block_size);
	draw_vert(game, block_size);
	draw_hor(game, block_size);
}
