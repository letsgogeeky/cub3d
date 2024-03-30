#include "cube.h"

static void	destroy_textures(t_game *game)
{
	free(game->map->north_texture->pixels);
	free(game->map->south_texture->pixels);
	free(game->map->west_texture->pixels);
	free(game->map->east_texture->pixels);
	if (game->map->door_texture != NULL)
		free(game->map->door_texture->pixels);
}

void	free_game(t_game *game)
{
	if (game->map != NULL)
	{
		destroy_textures(game);
		free_map_struct(game->map);
	}
	game->map = NULL;
	if (game->image != NULL)
		mlx_delete_image(game->mlx, game->image);
	game->image = NULL;
	if (game->minimap != NULL)
	{
		if (game->minimap->image != NULL)
			mlx_delete_image(game->mlx, game->minimap->image);
		free(game->minimap);
	}
	if (game->mlx != NULL)
		mlx_terminate(game->mlx);
	if (game != NULL)
		free(game);
	game = NULL;
}
