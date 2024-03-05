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
	game->graphics = malloc(sizeof(t_graphics));
	if (!game->graphics)
	{
		free_map_struct(game->map);
		game->map = NULL;
		free(game);
		game = NULL;
		return (NULL);
	}
	return (game);
}

t_game	*init_game(t_map *m)
{
	t_game	*game;

	game = allocate_game(m);
	if (!game)
		return (NULL);
	game->graphics->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!game->graphics->mlx)
	{
		free_game(game);
		return (NULL);
	}
	game->graphics->image = mlx_new_image(game->graphics->mlx, WIDTH, HEIGHT);
	if (!game->graphics->image)
	{
		free_game(game);
		mlx_terminate(game->graphics->mlx);
		return (NULL);
	}
	return (game);
}
