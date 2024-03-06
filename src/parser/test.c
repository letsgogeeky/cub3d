#include "../../include/cube.h"

void	test_parsing(t_map *m, int rows)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("North: %s\n", m->north_texture->path);
	printf("South: %s\n", m->south_texture->path);
	printf("West: %s\n", m->west_texture->path);
	printf("East: %s\n", m->east_texture->path);
	printf("Floor str: %s", m->floor_color->str_color);
	printf("Values: R: %i, G: %i, B: %i HEX: %#x\n", m->floor_color->red, m->floor_color->green, m->floor_color->blue, m->floor_color->hex_color_rgb);
	printf("Ceiling str: %s", m->ceiling_color->str_color);
	printf("Values: R: %i, G: %i, B: %i HEX: %#x\n", m->ceiling_color->red, m->ceiling_color->green, m->ceiling_color->blue, m->ceiling_color->hex_color_rgb);
	printf("\n");
	if (m->map != NULL)
	{
		while (i < rows)
		{
			while (m->map[i][j] != '\0')
				printf("%c", m->map[i][j++]);
			printf("|\n");
			j = 0;
			i++;
		}
	}
	printf("\n");
}

void	test_wall(t_map *m)
{
	printf("North: %s\n", m->north_texture->path);
	printf("South: %s\n", m->south_texture->path);
	printf("West: %s\n", m->west_texture->path);
	printf("East: %s\n", m->east_texture->path);
	printf("Floor: %s\n", m->floor_color->str_color);
	printf("Ceiling: %s\n", m->ceiling_color->str_color);
}
