#include "../../../include/cube.h"

double	vector_length(t_vector *vec)
{
	double	len;

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
		return(factor);
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

void	add_one_step(t_vector *side_dist, t_vector *step)
{
	side_dist->x += step->x;
	side_dist->y += step->y;
}

int	check_first_wall(t_game *game, t_vector factor, t_position *hitpoint)
{
	game->ray.side_dist_x.x = factor.x * game->ray.step_for_plus_x.x;
	game->ray.side_dist_x.y = factor.x * game->ray.step_for_plus_x.y;
	game->ray.side_dist_y.x = factor.y * game->ray.step_for_plus_y.x;
	game->ray.side_dist_y.y = factor.y * game->ray.step_for_plus_y.y;
	if (vector_length(&game->ray.side_dist_x) < \
		vector_length(&game->ray.side_dist_y))
	{
		hitpoint->x = game->player.pos.x + game->ray.side_dist_x.x;
		hitpoint->y = game->player.pos.y + game->ray.side_dist_x.y;
		if (hitpoint->x > 0 && hitpoint->y > 0)
			add_one_step(&game->ray.side_dist_x, &game->ray.step_for_plus_x);
	}
	else
	{
		hitpoint->x = game->player.pos.x + game->ray.side_dist_y.x;
		hitpoint->y = game->player.pos.y + game->ray.side_dist_y.y;
		if (hitpoint->x > 0 && hitpoint->y > 0)
			add_one_step(&game->ray.side_dist_y, &game->ray.step_for_plus_y);
	}
	if (check_hit(game, (*hitpoint)) == 1)
		return (1);
	return (0);
}

int	check_hit(t_game *game, t_position hitpoint)
{
	char	**map;
	int		i;
	int		j;
	int		test;

	map = game->map->map;
	i = (int)(hitpoint.x + 0.00001 * game->ray.angle.x);
	j = (int)(hitpoint.y + 0.00001 * game->ray.angle.y);
	// printf("check x %f -> %i\n", hitpoint.x, i);
	// printf("check y %f -> %i\n", hitpoint.y, j);
	// t_vector a, b;
	// a.x = (i + 0) * game->block_size;
	// a.y = (j + 0) * game->block_size;
	// b.x = (i + 1) * game->block_size;
	// b.y = (j + 1) * game->block_size;
	// draw_line(game, a, b, 0x00FF00FF);
	// a.y = (j + 1) * game->block_size;
	// b.y = (j + 0) * game->block_size;
	// draw_line(game, a, b, 0x00FF00FF);
	// a.x = (hitpoint.x) * game->block_size;
	// a.y = (hitpoint.y) * game->block_size + 10;
	// b.x = (hitpoint.x) * game->block_size;
	// b.y = (hitpoint.y) * game->block_size - 10;
	// draw_line(game, a, b, 0xFF0000FF);
	// a.x = (hitpoint.x) * game->block_size + 10;
	// a.y = (hitpoint.y) * game->block_size;
	// b.x = (hitpoint.x) * game->block_size - 10;
	// b.y = (hitpoint.y) * game->block_size;
	// draw_line(game, a, b, 0x0000FFFF);
	test = ft_strncmp(&map[j][i], "1", 1);
	printf("test i:%i j:%i\n Number: %c \n", i, j, map[j][i]);
	if (map[j][i] && test == 0)
		return (1);
	return (0);
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

void	calculate_hitpoint(t_game *game)
{
	bool		hit;
	t_vector	factor;
	t_position	hitpoint;
	t_vector	dx;
	t_vector	dy;
	int			flag;

	hit = false;
	factor = set_first_block_border(game);
	dx = game->ray.step_for_plus_x;
	dy = game->ray.step_for_plus_y;
	flag = 0;
	if (check_first_wall(game, factor, &hitpoint) == 1)
		hit = true;
	while (hit == false && hitpoint.x > 0 && hitpoint.y > 0)
	{
		if (vector_length(&game->ray.side_dist_x) == vector_length(&game->ray.side_dist_y))
		{
			if (vector_length(&dx) < vector_length(&dy))
				flag = 1;
		}
		if (flag == 1 || vector_length(&game->ray.side_dist_x) < vector_length(&game->ray.side_dist_y))
		{
			set_hitpoint(&hitpoint, game, 1);
			// hitpoint.x = game->player.pos.x + game->ray.side_dist_x.x;
			// hitpoint.y = game->player.pos.y + game->ray.side_dist_x.y;
			if (hitpoint.x > 0 && hitpoint.y > 0)
			{
				game->ray.side_dist_x.x += dx.x;
				game->ray.side_dist_x.y += dx.y;
			}
		}
		else
		{
			set_hitpoint(&hitpoint, game, 0);
			// hitpoint.x = game->player.pos.x + game->ray.side_dist_y.x;
			// hitpoint.y = game->player.pos.y + game->ray.side_dist_y.y;
			if (hitpoint.x > 0 && hitpoint.y > 0)
			{
				game->ray.side_dist_y.x += dy.x;
				game->ray.side_dist_y.y += dy.y;
			}
		}
		if(check_hit(game, hitpoint) == 1)
			break;
	}
	game->ray.hitpoint.x = hitpoint.x;
	game->ray.hitpoint.y = hitpoint.y;
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
		scalar = (2/((float)AMOUNT_RAYS_2D_FOV - 1));
	else
		scalar = 0;
	game->ray.angle.x = game->player.dir.x + game->player.plane.x * (1 - x * scalar);
	game->ray.angle.y = game->player.dir.y + game->player.plane.y * (1 - x * scalar);
}
