#include "../../../include/cube.h"

void	set_dda(t_position *hitpoint, t_game *game, t_vector *d, int version)
{
	t_vector	*step;

	step = &game->ray.side_dist_x;
	if (version == 0)
		step = &game->ray.side_dist_y;
	set_wall_direction(d, version, game);
	set_hitpoint(hitpoint, game, version);
	if (hitpoint->x > 0 && hitpoint->y > 0)
		add_one_step(step, d);
}

void	dda(t_position *hitpoint, t_game *game, t_vector *dx, t_vector *dy)
{
	int	flag;

	flag = 0;
	while (hitpoint->x > 0 && hitpoint->y > 0)
	{
		if (vector_length(&game->ray.side_dist_x) == \
			vector_length(&game->ray.side_dist_y))
		{
			if (vector_length(dx) < vector_length(dy))
				flag = 1;
		}
		if (flag == 1 || vector_length(&game->ray.side_dist_x) < \
			vector_length(&game->ray.side_dist_y))
			set_dda(hitpoint, game, dx, 1);
		else
			set_dda(hitpoint, game, dy, 0);
		if (check_hit(game, (*hitpoint)) == 1)
			return ;
	}
}

void	calculate_hitpoint(t_game *game)
{
	t_vector	factor;
	t_position	hitpoint;
	t_vector	dx;
	t_vector	dy;

	factor = set_first_block_border(game);
	dx = game->ray.step_for_plus_x;
	dy = game->ray.step_for_plus_y;
	if (check_first_wall(game, factor, &hitpoint) == 1)
	{
		game->ray.hitpoint.x = hitpoint.x;
		game->ray.hitpoint.y = hitpoint.y;
		return ;
	}
	dda(&hitpoint, game, &dx, &dy);
	game->ray.hitpoint.x = hitpoint.x;
	game->ray.hitpoint.y = hitpoint.y;
}
