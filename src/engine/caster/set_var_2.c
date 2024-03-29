#include "../../../include/cube.h"

t_vector	set_player_in_block(t_game *game)
{
	t_position	player;
	int			rounded_x;
	int			rounded_y;
	t_vector	mini_vector;

	player.x = game->player.pos.x;
	player.y = game->player.pos.y;
	rounded_x = (int)(player.x);
	rounded_y = (int)(player.y);
	mini_vector.x = fabs(player.x - (double)rounded_x);
	mini_vector.y = fabs(player.y - (double)rounded_y);
	return (mini_vector);
}

t_vector	set_first_block_border(t_game *game)
{
	t_vector	angle;
	t_vector	player_in_block;
	t_vector	factor;

	angle.x = game->ray.angle.x;
	angle.y = game->ray.angle.y;
	player_in_block = set_player_in_block(game);
	factor.x = 0;
	factor.y = 0;
	if (player_in_block.x == 0 && player_in_block.y == 0)
		return (factor);
	if (angle.x < 0)
		factor.x = (fabs(player_in_block.x));
	else if (angle.x > 0)
		factor.x = (fabs(1 - player_in_block.x));
	if (angle.y > 0)
		factor.y = (fabs(1 - player_in_block.y));
	else if (angle.y < 0)
		factor.y = (fabs(player_in_block.y));
	return (factor);
}

void	set_wall_direction(t_vector *vector, int version, t_game *game)
{
	if (version == 1)
	{
		if (vector->x > 0)
			game->ray.wall_texture = EAST;
		else
			game->ray.wall_texture = WEST;
	}
	else
	{
		if (vector->y > 0)
			game->ray.wall_texture = SOUTH;
		else
			game->ray.wall_texture = NORTH;
	}
}
