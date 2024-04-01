#include "cube.h"

t_game	*allocate_game(t_map *m)
{
	t_game	*game;

	if (m == NULL)
		return (ft_prerr(INV_MAP, NULL), NULL);
	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->map = m;
	game->minimap = malloc(sizeof(t_minimap));
	if (!game->minimap)
		return (NULL);
	return (game);
}

void	set_minimap_attributes(t_game *game)
{
	int	block_size;

	game->minimap->width = WIDTH / 4;
	game->minimap->height = HEIGHT / 4;
	block_size = game->minimap->height / game->map->rows;
	if (game->minimap->width / (game->map->cols) < block_size)
		block_size = game->minimap->width / (game->map->cols);
	game->block_size = block_size;
	game->minimap->p_radius = block_size / 4;
}

t_game	*init_game(t_map *m)
{
	t_game	*game;

	game = allocate_game(m);
	if (!game)
		return (NULL);
	set_minimap_attributes(game);
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!game->mlx)
		return (free_game(game), NULL);
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image)
		return (mlx_terminate(game->mlx), free_game(game), NULL);
	game->minimap->image = mlx_new_image(game->mlx, \
		game->minimap->width, game->minimap->height);
	if (!game->minimap->image)
		return (mlx_terminate(game->mlx), free_game(game), NULL);
	game->player = init_player(game->map);
	game->ray = init_ray();
	game->enable_minimap = true;
	game->enable_mouse = false;
	return (game);
}

void	open_n_draw(t_map *m)
{
	t_game	*game;

	game = init_game(m);
	if (game == NULL)
		return (ft_prerr(FAIL_GAME_INIT, NULL));
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) < 0)
		return (free_game(game));
	if (mlx_image_to_window(game->mlx, game->minimap->image, \
		WIDTH - game->minimap->width - 10, 10) < 0)
		return (free_game(game));
	load_doors(game);
	if (game->map->door_texture->path == NULL && game->map->doors_count > 0)
		return (ft_prerr(FAIL_DOOR_TEXTURE, NULL), free_game(game));
	draw_block(game);
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_loop_hook(game->mlx, controls_directions, game);
	mlx_key_hook(game->mlx, ft_controls_extra, game);
	mlx_cursor_hook(game->mlx, (mlx_cursorfunc)mouse_hook, game);
	mlx_loop(game->mlx);
	free_game(game);
	return ;
}
