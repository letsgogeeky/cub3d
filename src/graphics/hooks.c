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
		return (rotate(game, true, 1), draw_block(game));
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		return (rotate(game, false, 1), draw_block(game));
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
	if (key.key == MLX_KEY_SPACE && key.action == MLX_RELEASE)
	{
		game->enable_mouse = !game->enable_mouse;
		if(!game->enable_mouse)
		{
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
			printf("Mouse disabled\n");
		}
		else
			printf("Mouse enabled\n");
	}
	if (key.key == MLX_KEY_M && key.action == MLX_RELEASE)
	{
		game->enable_minimap = !game->enable_minimap;
		draw_block(game);
	}
}

void	mouse_hook(void *param)
{
	t_game	*game;
	int		x;
	int		y;
	double	angle;

	game = param;
	if (!game->enable_mouse)
		return ;
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	mlx_get_mouse_pos(game->mlx, &x, &y);
	angle = (double)(x - (WIDTH / 2));
	if (angle < 0)
		rotate(game, true, 0.3);
	else
		rotate(game, false, 0.3);
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
	draw_block(game);
}
