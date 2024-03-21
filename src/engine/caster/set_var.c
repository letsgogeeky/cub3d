#include "../../../include/cube.h"

double	vector_length(t_vector *vec)
{
	double	len;

	len = sqrt((vec->x) * (vec->x) + (vec->y) * (vec->y));
	return (len);
}

void	add_one_step(t_vector *side_dist, t_vector *step)
{
	side_dist->x += step->x;
	side_dist->y += step->y;
}

void	set_hitpoint(t_position *hitpoint, t_game *game, int i)
{
	if (i > 0)
	{
		hitpoint->x = game->player.pos.x + game->ray.side_dist_x.x;
		hitpoint->y = game->player.pos.y + game->ray.side_dist_x.y;
	}
	else
	{
		hitpoint->x = game->player.pos.x + game->ray.side_dist_y.x;
		hitpoint->y = game->player.pos.y + game->ray.side_dist_y.y;
	}
}

void	set_steps(t_game *game)
{
	float		factor_x;
	float		factor_y;

	factor_x = fabs(1 / game->ray.angle.x);
	factor_y = fabs(1 / game->ray.angle.y);
	game->ray.step_for_plus_x.y = game->ray.angle.y * factor_x;
	game->ray.step_for_plus_x.x = game->ray.angle.x * factor_x;
	game->ray.step_for_plus_y.y = game->ray.angle.y * factor_y;
	game->ray.step_for_plus_y.x = game->ray.angle.x * factor_y;
}

void	set_angle(t_game *game, int x)
{
	float		scalar;

	if (AMOUNT_RAYS_2D_FOV > 1)
		scalar = (2 / ((float)AMOUNT_RAYS_2D_FOV - 1));
	else
		scalar = 0;
	game->ray.angle.x = game->player.dir.x + \
		game->player.plane.x * (1 - x * scalar);
	game->ray.angle.y = game->player.dir.y + \
		game->player.plane.y * (1 - x * scalar);
}
