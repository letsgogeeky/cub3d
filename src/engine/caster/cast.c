#include "../../../include/cube.h"

t_ray	init_ray(void)
{
	t_ray	ray;

	ray.dir.x = 0;
	ray.dir.y = 0;
	ray.angle.x = 0;
	ray.angle.y = 0;
	ray.step_for_plus_x.x = 0;
	ray.step_for_plus_x.y = 0;
	ray.step_for_plus_y.x = 0;
	ray.step_for_plus_y.y = 0;
	ray.hitpoint.x = 0;
	ray.hitpoint.y = 0;
	ray.side_dist_x.x = 0;
	ray.side_dist_x.y = 0;
	ray.side_dist_y.x = 0;
	ray.side_dist_y.y = 0;
	ray.delta_dist.x = 0;
	ray.delta_dist.y = 0;
	ray.map.x = 0;
	ray.map.y = 0;
	ray.len_to_wall = 0;
	ray.len_to_plane = 0;
	ray.wall_height = 0;
	return (ray);
}

void	visualize_2d_ray(t_game *game, int color)
{
	int			x;

	x = 0;
	while (x < AMOUNT_RAYS_2D_FOV)
	{
		set_angle(game, x, AMOUNT_RAYS_2D_FOV);
		set_steps(game);
		calculate_hitpoint(game);
		draw_ray(game, color);
		x++;
	}
	return ;
}

void	visualize_3d(t_game *game)
{
	int			x;
	t_column	column;

	x = 0;
	while (x < WIDTH)
	{
		set_angle(game, x, WIDTH);
		set_steps(game);
		calculate_hitpoint(game);
		calculate_length_to_plane(game);
		column = calculate_height(game);
		draw_column(game, &column, x);
		x++;
	}
	return ;
}
