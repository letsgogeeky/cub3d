#include "cube.h"

int	main()
{
	test_with_mocks();
	t_game	*game;

	game = init_game();
	if (!game)
	{
		printf("Error: failed to initialize game\n");
		return (1);
	}
	mlx_image_to_window(game->graphics->mlx, game->graphics->image, 0, 0);
	mlx_loop(game->graphics->mlx);
	return (0);
}
