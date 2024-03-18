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
	mini_vector.x = fabs(player.x - (double)rounded_x);
	mini_vector.y = fabs(player.y - (double)rounded_y);

	printf("player: %f/%f rounded: %i/%i mini vector: %f/%f\n", player.x, player.y, rounded_x, rounded_y, mini_vector.x, mini_vector.y);
	return (mini_vector);
	game = NULL;
}


// t_position	dda(t_game *game)
// {
// 	double			length_a;
// 	t_vector		a;
// 	t_vector		b;
// 	double			length_b;
// 	t_position		hitpoint;


// 	a.x = /*game->player.pos.x*/ game->ray.side_dist.x + dx.x;
// 	a.y = /*game->player.pos.y*/ game->ray.side_dist.y + dx.y;
// 	b.x = /*game->player.pos.x*/ game->ray.side_dist.x + dy.x;
// 	b.y = /*game->player.pos.y*/ game->ray.side_dist.y + dy.y;
// 	length_a = vector_length(&a);

// 	length_b = vector_length(&b);
// 	printf("vektor a: %f, vektor b = %f\n", length_a, length_b);
// 	if (length_a > length_b)
// 	{
// 		game->ray.side_dist.x += dy.x;
// 		game->ray.side_dist.y += dy.y;
// 	}
// 	else
// 	{
// 		game->ray.side_dist.x += dx.x;
// 		game->ray.side_dist.y += dx.y;
// 	}
// 	hitpoint.x = game->player.pos.x + game->ray.side_dist.x;
// 	hitpoint.y = game->player.pos.y + game->ray.side_dist.y;
// 	printf("dda hitpoint: %f %f\n", game->ray.side_dist.x, game->ray.side_dist.y);
// 	return (hitpoint);
// }

double	set_first_block_border(t_game *game)
{
	t_vector	angle;
	t_vector	player_in_block;
	double		factor;

	angle.x = game->ray.angle.x;
	angle.y = game->ray.angle.y;
	player_in_block = set_player_in_block(game);
	factor = 0;
	if (player_in_block.x == 0 && player_in_block.y == 0)
		return (factor);
	else if (angle.x < 0 && fabs(angle.y/angle.x) <= 1)
	{
		factor = fabs(angle.x);
		// printf("A\n");
	}
		//view direction west;
	else if (angle.x >= 0 && fabs(angle.y/angle.x) <= 1)
	{
		factor = fabs(1 - angle.x);
		// printf("B\n");
	}
		//view direction east
	else if (angle.y >= 0 && fabs(angle.x/angle.y) <= 1)
	{
		factor = fabs(1 - angle.y);
		// printf("C\n");
	}
		//view direction south
	else if (angle.y < 0 && fabs(angle.x/angle.y) <= 1)
	{
		// printf("D\n");
		factor = fabs(angle.y);
	}
	// printf("Angle: %f/%f Player: %f/%f first factor: %f\n", angle.x, angle.y, player_in_block.x, player_in_block.y, factor);
	return (factor);
}

int	check_hit(t_game *game, t_position hitpoint)
{
	char	**map;
	int		i;
	int		j;
	int		test;

	map = game->map->map;
	i = (int)hitpoint.x;
	j = (int)hitpoint.y;
	test = ft_strncmp(&map[j][i], "1", 1);
	// test = ft_atoi(&map[i][j]);
	printf("test i:%i j:%i\n Number: %c \n", i, j, map[j][i]);
	if (map[j][i] && test == 0)
		return (1);
	return (0);
}

int	check_first_wall(t_game *game, double factor, t_position	*hitpoint)
{
	// printf("FAKTOR %f\n", factor);
	game->ray.side_dist_x.x = factor * game->ray.angle.x;
	game->ray.side_dist_x.y = factor * game->ray.angle.y;
	game->ray.side_dist_y.x = factor * game->ray.angle.x;
	game->ray.side_dist_y.y = factor * game->ray.angle.y;
	hitpoint->x = game->player.pos.x + game->ray.side_dist_x.x;
	hitpoint->y = game->player.pos.y + game->ray.side_dist_x.y;
	// printf("*****factor: %f, hitpoint = %f/%f\n", factor, hitpoint->x, hitpoint->y);
	// printf("Aray_side_dist_x = %f / %f ray_side_dist_y = %f / %f\n", game->ray.side_dist_x.x, game->ray.side_dist_x.y, game->ray.side_dist_y.x, game->ray.side_dist_y.y);
	if (check_hit(game, (*hitpoint)) == 1)
		return (1);
	game->ray.side_dist_x.x += game->ray.step_for_plus_x.x;
	game->ray.side_dist_x.y += game->ray.step_for_plus_x.y;
	game->ray.side_dist_y.x += game->ray.step_for_plus_y.x;
	game->ray.side_dist_y.y += game->ray.step_for_plus_y.y;
	// printf("Bray_side_dist_x = %f / %f ray_side_dist_y = %f / %f \n", game->ray.side_dist_x.x, game->ray.side_dist_x.y, game->ray.side_dist_y.x, game->ray.side_dist_y.y);
	return (0);
}

void	calculate_hitpoint(t_game *game)
{
	bool		hit;
	double		factor;
	t_position	hitpoint;
	t_vector	dx;
	t_vector	dy;


	hit = false;
	factor = set_first_block_border(game);
	dx = game->ray.step_for_plus_x;
	dy = game->ray.step_for_plus_y;
	// printf("dx = %f /%f dy = %f / %f \n", dx.x, dx.y, dy.x, dy.y);
	if (check_first_wall(game, factor, &hitpoint) == 1)
		hit = true;
	// printf("firstcheckover\n\n");

	while (hit == false && hitpoint.x > 0 && hitpoint.y > 0)
	{
		// printf("hitpoint = %f / %f \n", hitpoint.x, hitpoint.y);
		if(check_hit(game, hitpoint) == 1)
		{
			//set_direction_wall(game) also welche texture;
			hit = true;
			break;
		}
		// printf("calc hit\n\n");
		// printf("ray_side_dist_x = %f / %f ray_side_dist_y = %f / %f dx %f/%f dy %f/%f\n", game->ray.side_dist_x.x, game->ray.side_dist_x.y, game->ray.side_dist_y.x, game->ray.side_dist_y.y, dx.x, dx.y, dy.x, dy.y);
		if (vector_length(&game->ray.side_dist_x) < vector_length(&game->ray.side_dist_y))
		{
			hitpoint.x = game->player.pos.x + game->ray.side_dist_x.x;
			hitpoint.y = game->player.pos.y + game->ray.side_dist_x.y;
			if (hitpoint.x > 0 && hitpoint.y > 0)
			{
				game->ray.side_dist_x.x += dx.x;
				game->ray.side_dist_x.y += dx.y;
			}
			// printf("oben\n");
		}
		else
		{
			hitpoint.x = game->player.pos.x + game->ray.side_dist_y.x;
			hitpoint.y = game->player.pos.y + game->ray.side_dist_y.y;
			if (hitpoint.x > 0 && hitpoint.y > 0)
			{
				game->ray.side_dist_y.x += dy.x;
				game->ray.side_dist_y.y += dy.y;
			}
	
			// printf("unten\n");
		}
		// printf("hitpoint = %f / %f \n", hitpoint.x, hitpoint.y);
		// hitpoint = dda(game);
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
	printf("step_x = x %f y %f\n", game->ray.step_for_plus_x.x, game->ray.step_for_plus_x.y);
	printf("step_y = x %f y %f\n", game->ray.step_for_plus_y.x, game->ray.step_for_plus_y.y);

}

void	set_angle(t_game *game, int x)
{
	float		scalar;

	scalar = (2/((float)AMOUNT_RAYS_2D_FOV - 1));
	game->ray.angle.x = game->player.dir.x + game->player.plane.x * (1 - x * scalar);
	game->ray.angle.y = game->player.dir.y + game->player.plane.y * (1 - x * scalar);
	printf("angle: x %f y %f\n", game->ray.angle.x, game->ray.angle.y);
}
