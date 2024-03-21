# include "cube.h"

t_game	*allocate_game(t_map *m)
{
	t_game	*game;

	if (m == NULL)
		return (ft_prerr(INV_MAP, NULL), NULL);
	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->map = m;
	game->data = malloc(sizeof(t_data));
	if (!game->data)
	{
		free(game);
		return (NULL);
	}
	game->data->rays = malloc(sizeof(t_ray) * WIDTH);
	if (!game->data->rays)
	{
		free(game->data);
		free(game);
		return (NULL);
	}
	game->minimap = malloc(sizeof(t_minimap));
	if (!game->minimap)
	{
		free(game->data->rays);
		free(game->data);
		free(game);
		return (NULL);
	}
	return (game);
}

void	set_minimap_attributes(t_game *game)
{
	int block_size;

	game->minimap->width = WIDTH / 2;
	game->minimap->height = HEIGHT / 2;
	game->minimap->arrows_count = 11;
	block_size = game->minimap->height / game->map->rows;
	if (game->minimap->width / (game->map->cols) < block_size)
		block_size = game->minimap->width / (game->map->cols);
	game->block_size = block_size;
	game->minimap->p_radius = block_size / 4;
}

void	compute_block_size(t_game *game)
{
	int	block_size;

	block_size = game->minimap->height / game->map->rows;
	if (game->minimap->width / (game->map->cols) < block_size)
		block_size = game->minimap->width / (game->map->cols);
	game->block_size = block_size;
}

t_game	*init_game(t_map *m)
{
	t_game	*game;

	game = allocate_game(m);
	if (!game)
		return (NULL);
	set_minimap_attributes(game);
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!game->mlx)
	{
		free_game(game);
		return (NULL);
	}
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image)
	{
		free_game(game);
		mlx_terminate(game->mlx);
		return (NULL);
	}
	game->minimap->image = mlx_new_image(game->mlx, game->minimap->width, game->minimap->height);
	if (!game->minimap)
	{
		free_game(game);
		mlx_delete_image(game->mlx, game->image);
		mlx_terminate(game->mlx);
		return (NULL);
	}
	game->player = init_player(game->map);
	game->ray = init_ray();
	compute_block_size(game);
	return (game);
}

// void	ft_keyhook(mlx_key_data_t keydata, void *param)
// {
	
// 	if (keydata.key == MLX_KEY_W && keydata.action == MLX_REPEAT)
// 		move_forward();
// 	if (keydata.key == MLX_KEY_A && keydata.action == MLX_REPEAT)
// 		turn_left();
// 	if (keydata.key == MLX_KEY_S && keydata.action == MLX_REPEAT)
// 		move_backwards();
// 	if (keydata.key == MLX_KEY_D && keydata.action == MLX_REPEAT)
// 		turn_right();
// 	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_REPEAT)
// 		turn_left();
// 	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_REPEAT)
// 		turn_right();

// }


void	ft_hook(void *param) // need to try if two loops are possible if different param are needed
{
	mlx_t	*mlx;
	t_game	*game;

	game = param;
	mlx = game->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	else if (mlx_is_key_down(mlx, MLX_KEY_W))
		return (move_forward(game), draw_block(game));
	else if (mlx_is_key_down(mlx, MLX_KEY_A))
		return (move_left(game), draw_block(game));
	else if (mlx_is_key_down(mlx, MLX_KEY_S))
		return (move_backward(game), draw_block(game));
	else if (mlx_is_key_down(mlx, MLX_KEY_D))
		return (move_right(game), draw_block(game));
	else if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		return (rotate(game, true), draw_block(game));
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		return (rotate(game, false), draw_block(game));
}

void	free_game(t_game *game)
{
	if (game->map != NULL)
		free_map_struct(game->map);
	game->map = NULL;
	if (game->data != NULL)
		free(game->data);
	game->data = NULL;
	if (game != NULL)
		free(game);
	game = NULL;
}

void	open_n_draw(t_map *m)
{
	t_game	*game;

	game = init_game(m);
	if (game == NULL)
	{
		ft_prerr(FAIL_GAME_INIT, NULL);
		return ;
	}
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) < 0)
	{
		free_game(game);
		mlx_terminate(game->mlx);
		return ;
	}
	if (mlx_image_to_window(game->mlx, game->minimap->image, WIDTH - game->minimap->width - 10, 10) < 0)
	{
		free_game(game);
		mlx_terminate(game->mlx);
		return ;
	}
	// raycast(game);
	draw_block(game);
	// do_raycast(game);
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_game(game);
	return ;
}
