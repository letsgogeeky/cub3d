#include "../../../include/cube.h"

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
	int				i;
	int				color;
	// mlx_texture_t	*normal;
	// mlx_texture_t	*resized;

	i = column->end_ceiling;
	// printf("Wall: %u\n", game->ray.wall_texture);
	// printf("%s\n", game->map->north_texture->path);
	// normal = choose_texture(game);
	// printf("///////%i %i\n", normal->height, normal->width);
	// resze_tex(normal, game, column, x);
	while (i < column->start_floor)
	{
		color = 0xFFFFFFFF;
		mlx_put_pixel(game->image, x, i, color);
		i++;
	}
}

void	draw_complete(t_game *game, int x)
{
	int	i;

	i = 0;
	while (i < HEIGHT)
	{
		mlx_put_pixel(game->image, x, i, 0xFFFFFFFF);
		i++;
	}
}

void	draw_column(t_game *game, t_column *column, int x)
{
	if (column->wall_height + 2 >= HEIGHT)
	{
		draw_complete(game, x);
		return ;
	}
	draw_image(game, column, x);
	draw_ceiling(game, column, x);
	draw_floor(game, column, x);
}

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
