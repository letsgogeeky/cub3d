#include "cube.h"

void	ft_controls(void *param)
{
	mlx_t   *mlx;
    t_game  *game;

    game = param;
    mlx = game->mlx;
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
