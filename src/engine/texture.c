#include "cube.h"

unsigned int	*load_texture_pixels(mlx_texture_t *texture)
{
	unsigned int	*data;
	u_int32_t		i;
	u_int32_t		j;

	data = malloc(sizeof(unsigned int) * texture->width * texture->height + 4);
	if (!data)
		return (NULL);
	i = -1;
	while (++i < texture->height)
	{
		j = -1;
		while (++j < texture->width)
		{
			data[i * texture->width + j] = colorcode(
					texture->pixels[i * texture->width * 4 + j * 4],
					texture->pixels[i * texture->width * 4 + j * 4 + 1],
					texture->pixels[i * texture->width * 4 + j * 4 + 2],
					texture->pixels[i * texture->width * 4 + j * 4 + 3]
					);
		}
	}
	data[texture->width * texture->height] = 0;
	return (data);
}

int	check_textures(t_map *m)
{
	if (m->north_texture->tex == NULL || \
		m->south_texture->tex == NULL || \
		m->west_texture->tex == NULL || \
		m->east_texture->tex == NULL || \
		m->door_texture->tex == NULL)
		return (1);
	return (0);
}

void	update_texture(t_texture *texture)
{
	texture->tex = mlx_load_png(texture->path);
	if (texture->tex == NULL)
		return ;
	texture->pixels = load_texture_pixels(texture->tex);
	texture->width = texture->tex->width;
	texture->height = texture->tex->height;
	mlx_delete_texture(texture->tex);
}

void	load_textures(t_map *map)
{
	if (map->north_texture->path == NULL || \
		map->south_texture->path == NULL || \
		map->west_texture->path == NULL || \
		map->east_texture->path == NULL)
		return ;
	update_texture(map->north_texture);
	update_texture(map->south_texture);
	update_texture(map->west_texture);
	update_texture(map->east_texture);
	if (map->door_texture->path)
		update_texture(map->door_texture);
}

t_texture	*choose_texture(t_game *game)
{
	int	i;
	int	j;

	i = (int)(game->ray.hitpoint.x + 0.00001 * game->ray.angle.x);
	j = (int)(game->ray.hitpoint.y + 0.00001 * game->ray.angle.y);
	if (j >= 0 && i >= 0 && j < game->map->rows && i < game->map->cols && \
		game->map->map[j][i] == DOOR && !door_is_open(game, j, i))
		return (game->map->door_texture);
	if (game->ray.wall_texture == NORTH)
		return (game->map->north_texture);
	else if (game->ray.wall_texture == SOUTH)
		return (game->map->south_texture);
	else if (game->ray.wall_texture == EAST)
		return (game->map->east_texture);
	else if (game->ray.wall_texture == WEST)
		return (game->map->west_texture);
	else
		return (NULL);
}
