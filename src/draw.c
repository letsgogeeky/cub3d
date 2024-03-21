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
	while (cnt < game->map->rows)
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

void	cast_wall(t_game *game, int size, int x, int y, int color)
{
	int	tmp_x;
	int	x_max;
	int	y_max;

	tmp_x = x;
	x_max = x + size;
	y_max = y + size;
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
void	clear_area(t_game *game)
{
	int	x;
	int	y;

	x = game->player.pos.x * game->block_size;
	y = game->player.pos.y * game->block_size;
	fill_block(game, game->block_size, x, y, 0x00FFA000);
}

void	clear_image(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			mlx_put_pixel(game->image, x, y, 0x00000000);
			x++;
		}
		x = 0;
		y++;
	}
}

void	show_player(t_game *game)
{
	int	x;
	int	y;

	ft_printf("Direction: %f, %f\n", game->player.dir.x, game->player.dir.y);
	ft_printf("Position: %f, %f\n", game->player.pos.x, game->player.pos.y);
	x = game->player.pos.x * game->block_size;
	y = game->player.pos.y * game->block_size;
	ft_printf("x: %d, y: %d\n", x, y);
	// fill_block(game, game->block_size, x, y, 0x00FFFFFF);
	visualize_2d_ray(game, 0xFF0000FF);
}

void	draw_block(t_game *game)
{
	int	block_size;
	int	x;
	int	y;
	int	i;
	int	j;

	block_size = HEIGHT / game->map->rows;
	x = 0;
	y = 0;
	i = 0;
	j = 0;
	if (WIDTH / (game->map->cols) < block_size)
		block_size = WIDTH / (game->map->cols);
	clear_image(game);
	draw_vert(game, block_size);
	draw_hor(game, block_size);
	while (i < game->map->rows)
	{
		while (game->map->map[i][j] != '\0')
		{
			if (game->map->map[i][j] == '1')
				fill_block(game, block_size, x, y, 0x000000FF);
			// else if (ft_strchr("NSEW", game->map->map[i][j]) != NULL)
			// 	fill_block(game, block_size, x, y, 0x00FFFFFF);
			x = x + block_size;
			j++;
		}
		j = 0;
		x = 0;
		i++;
		y = y + block_size;
	}
	show_player(game);
}
