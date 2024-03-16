#include "../../../include/cube.h"

double	vector_length(t_vector *vec)
{
	int	len;

	len = sqrt((vec->x)*(vec->x) + (vec->y)*(vec->y));
	return (len);
}

t_vector	set_player_in_block(t_game *game)
{
	t_position	player;
	int			rounded_x;
	int			rounded_y;
	t_vector	mini_vector;

	player.x = game->player.pos.x;
	player.y = game->player.pos.y;
	rounded_x = (int)(player.x + 0.5);
	rounded_y = (int)(player.y + 0.5);
	mini_vector.x = player.x - (double)rounded_x;
	mini_vector.y = player.y - (double)rounded_y;
	return (mini_vector);
}

float	set_first_block_border(t_game *game)
{
	t_vector	angle;
	t_vector	player_in_block;
	float		factor;

	angle.x = game->ray.angle.x;
	angle.y = game->ray.angle.y;
	player_in_block = set_player_in_block(game);
	factor = 1;
	if (angle.x < 0 && fabs(angle.y/angle.x) <= 1)
		factor = fabs(angle.x);
		//view direction west;
	else if (angle.x >= 0 && angle.y/angle.x <= 1)
		factor = fabs(1 - angle.x);
		//view direction east
	else if (angle.y >= 0 && angle.x/angle.y <= 1)
		factor = fabs(1 - angle.y);
		//view direction south
	else if (angle.y < 0 && angle.x/angle.y <= 1)
		factor = fabs(angle.y);
	return (factor);
}

int	check_hit(t_game *game, t_position hitpoint)
{
	char	**map;
	int		i;
	int		j;

	map = game->map->map;
	i = (int)hitpoint.x;
	j = (int)hitpoint.y;
	if (ft_strncmp(&map[j][i], "1", 1) == 0)
		return (1);
	return (0);
}

int	check_first_wall(t_game *game, float factor, t_position	*hitpoint)
{
	game->ray.side_dist.x = factor * game->ray.angle.x;
	game->ray.side_dist.y = factor * game->ray.angle.y;
	hitpoint->x = game->player.pos.x + game->ray.side_dist.x;
	hitpoint->y = game->player.pos.y + game->ray.side_dist.y;
	if (check_hit(game, (*hitpoint)) == 1)
		return (1);
	return (0);
}

t_position	dda(t_game *game)
{
	t_vector	dx;
	t_vector	dy;
	double		length_a;
	t_vector	a;
	t_vector	b;
	double		length_b;
	t_position	hitpoint;


	dx = game->ray.step_for_plus_x;
	dy = game->ray.step_for_plus_y;
	a.x = game->player.pos.x + game->ray.side_dist.x + dx.x;
	a.y = game->player.pos.y + game->ray.side_dist.y + dx.y;
	b.x = game->player.pos.x + game->ray.side_dist.x + dy.x;
	b.y = game->player.pos.y + game->ray.side_dist.y + dy.y;
	length_a = vector_length(&a);
	length_b = vector_length(&b);
	if (length_a > length_b)
	{
		game->ray.side_dist.x += dy.x;
		game->ray.side_dist.y += dy.y;
	}
	else
	{
		game->ray.side_dist.x += dx.x;
		game->ray.side_dist.y += dx.y;
	}
	hitpoint.x = game->player.pos.x + game->ray.side_dist.x;
	hitpoint.y = game->player.pos.y + game->ray.side_dist.y;
	return (hitpoint);
}

void	calculate_hitpoint(t_game *game)
{
	bool		hit;
	float		factor;
	t_position	hitpoint;

	hit = false;
	factor = set_first_block_border(game);
	if (check_first_wall(game, factor, &hitpoint) == 1)
		hit = true;
	while (hit == false)
	{
		hitpoint = dda(game);
		if(check_hit(game, hitpoint) == 1)
		{
			//set_direction_wall(game) also welche texture;
			hit = true;
		}
	}
	game->ray.hitpoint.x = hitpoint.x;
	game->ray.hitpoint.y = hitpoint.y;
}

void	set_steps(t_game *game)
{
	t_vector	angle;
	float		factor_x;
	float		factor_y;

	angle = game->ray.angle;
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

	scalar = (2/((float)AMOUNT_RAYS_2D_FOV - 1));
	game->ray.angle.x = game->player.dir.x + game->player.plane.x * (1 - x * scalar);
	game->ray.angle.y = game->player.dir.y + game->player.plane.y * (1 - x * scalar);
}
