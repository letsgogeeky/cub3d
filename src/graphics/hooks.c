#include "cube.h"

void	ft_hook(void *param)
{
	mlx_t	*mlx;
	t_game	*game;

	game = param;
	mlx = game->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	else if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		return (rotate(game, true), draw_block(game));
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		return (rotate(game, false), draw_block(game));
}

void	controls_directions(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		return (move_forward(game), draw_block(game));
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		return (move_left(game), draw_block(game));
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		return (move_backward(game), draw_block(game));
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		return (move_right(game), draw_block(game));
}

void	ft_controls_extra(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = param;
	if (key.key == MLX_KEY_F && key.action == MLX_PRESS)
		return (door_control(game), draw_block(game));
}