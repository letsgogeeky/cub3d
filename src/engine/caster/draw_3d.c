#include "../../../include/cube.h"

// void	set_radian_angle(t_game *game, int x, int amnt_rays)
// {
// 	double	radian;
// 	double	scalar;

// 	radian = atan(0.66 / 1);
// 	if (amnt_rays > 1)
// 		scalar = 2 / (2 * radian) / (amnt_rays - 1);
// 	else
// 		scalar = 0;
// 	game->ray.angle.x = game->player.dir.x + \
// 		game->player.plane.x * (1 - (x * scalar));
// 	game->ray.angle.y = game->player.dir.y + \
// 		game->player.plane.y * (1 - (x * scalar));
// }

// void	calculate_length_to_plane(t_game *game)
// {
// 	double		len;
// 	t_vector	hit;
// 	t_vector	dir;
// 	double		denominator;
// 	double		radian;

// 	len = game->ray.len_to_wall;
// 	hit = game->ray.hitpoint;
// 	dir = game->player.dir;
// 	denominator = sqrt(hit.x * hit.x + hit.y * hit.y) + sqrt(dir.x * dir.x + dir.y * dir.y);
// 	// if (lr == 0)
// 	// {
// 	radian = acos((hit.x * dir.x + hit.y * dir.y) / denominator);
// 	// }
// 	// else
// 	// {
// 	// 	// denominator = sqrt(hit.x * hit.x + hit.y * hit.y) + sqrt(dir.x * dir.x + dir.y * dir.y);
// 	// 	radian = acos((hit.x * dir.x + hit.y * dir.y) / denominator);
// 	// }
// 	printf("WINKEL: %f ", cos(radian));
// 	game->ray.len_to_plane = cos(radian) * len;
// 		printf("radian: %f len to plane: %f len to wall %f\n", radian, game->ray.len_to_plane, game->ray.len_to_wall);
// }

void	draw_ceiling(t_game *game, t_column *column, int x)
{
	int	i;
	int	color;

	i = 0;
	color = game->map->ceiling_color->hex_color_rgb;
	while (i < column->end_ceiling)
	{
		mlx_put_pixel(game->image, x, i, color);
		i++;
	}
}

void	draw_floor(t_game *game, t_column *column, int x)
{
	int	i;
	int	color;

	i = column->start_floor;
	color = game->map->floor_color->hex_color_rgb;
	while (i < HEIGHT)
	{
		mlx_put_pixel(game->image, x, i, color);
		i++;
	}
}

void	draw_image(t_game *game, t_column *column, int x)
{
	int	i;
	int	color;

	i = column->end_ceiling;
	while (i < column->start_floor)
	{
		color = game->map->floor_color->hex_color_rgb;
		mlx_put_pixel(game->image, x, i, color);
		i++;
	}
}

void	draw_column(t_game *game, t_column *column, int x)
{
	draw_ceiling(game, column, x);
	draw_floor(game, column, x);
	draw_image(game, column, x);
}

t_column	*calculate_height(t_game *game)
{
	t_column	column;

	game->ray.wall_height = 1 / game->ray.len_to_plane * HEIGHT;
	column.wall_height = game->ray.wall_height;
	column.end_ceiling = (HEIGHT - column.wall_height) / 2;
	column.start_floor = column.end_ceiling + game->ray.wall_height;
	return (&column);
}

void	calculate_length_to_plane(t_game *game)
{
	double		len;
	t_vector	hit;
	t_vector	dir;
	double		radian;

	len = game->ray.len_to_wall;
	hit = game->ray.hitpoint;
	dir = game->player.dir;
	radian = acos((hit.x * dir.y + hit.y * dir.x) / \
		(sqrt(hit.x * hit.x + hit.y * hit.y) + \
		sqrt(dir.x * dir.x + dir.y * dir.y)));
	game->ray.len_to_plane = cos(radian) * len;
}

void	visualize_3d(t_game *game)
{
	int			x;
	t_column	*column;

	x = 0;
	while (x < WIDTH)
	{
		set_angle(game, x, WIDTH);
		set_steps(game);
		calculate_hitpoint(game);
		calculate_length_to_plane(game);
		column = calculate_height(game);
		draw_column(game, column, x);
		x++;
	}
	return ;
}
