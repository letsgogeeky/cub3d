# include "cube.h"

t_game	*allocate()
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
	{
		free(game);
		return (NULL);
	}
	game->graphics = malloc(sizeof(t_graphics));
	if (!game->graphics)
	{
		free(game->map);
		free(game);
		return (NULL);
	}
	return (game);
}

t_game	*init_game(void)
{
	t_game	*game;

	game = allocate();
	if (!game)
		return (NULL);
	game->graphics->width = WIDTH;
	game->graphics->height = HEIGHT;
	game->graphics->mlx = mlx_init(game->graphics->width, game->graphics->height, "cub3d", false);
	if (!game->graphics->mlx)
	{
		free(game->graphics);
		free(game->map);
		free(game);
		return (NULL);
	}
	game->graphics->image = mlx_new_image(game->graphics->mlx, game->graphics->width, game->graphics->height);
	if (!game->graphics->image)
	{
		free(game->graphics->mlx);
		free(game->graphics);
		free(game->map);
		free(game);
		return (NULL);
	}
	return (game);
}
