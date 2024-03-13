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
	return (game);
}

void	compute_block_size(t_game *game)
{
	int	block_size;

	block_size = HEIGHT / game->map->rows;
	if (WIDTH / (game->map->cols) < block_size)
		block_size = WIDTH / (game->map->cols);
	game->block_size = block_size;
}

t_game	*init_game(t_map *m)
{
	t_game	*game;

	game = allocate_game(m);
	if (!game)
		return (NULL);
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
	mlx = game->graphics->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	else if (mlx_is_key_down(mlx, MLX_KEY_W))
		return (clear_area(game), move_forward(game));
	else if (mlx_is_key_down(mlx, MLX_KEY_A))
		return (clear_area(game), move_left(game));
	else if (mlx_is_key_down(mlx, MLX_KEY_S))
		return (clear_area(game), move_backward(game));
	else if (mlx_is_key_down(mlx, MLX_KEY_D))
		return (clear_area(game), move_right(game));
	else if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		return (clear_area(game), turn_left(game));
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		return (clear_area(game), turn_right(game));
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
	// raycast(game);
	// draw_block(game);
	do_raycast(game);
	mlx_loop_hook(game->mlx, ft_hook, game->mlx);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_game(game);
	return ;
}
