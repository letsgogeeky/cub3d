#ifndef CUBE_H
# define CUBE_H

# include "../lib/ft-baselib/include/baselib.h"
# include <stdio.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_texture
{
	char	*path;
}		t_texture;

typedef struct s_color
{
	char	*str_color;
	int		red;
	int		green;
	int		blue;
}		t_color;

typedef struct s_map // every element is allocated and has to be freed if failure occures
{
	t_texture	*north_texture;
	t_texture	*south_texture;
	t_texture	*west_texture;
	t_texture	*east_texture;
	t_color		*floor_color;
	t_color		*ceiling_color;
	char				**map;
}		t_map;

//map_init.c
t_map	*parse(t_map *m, int fd, char *argv);
int		parse_map(int fd, t_map *m, char *tmp, char *argv);
int		fill_map(t_map *m, int fd, int rows, int max_length);
void	set_char(int i, char *tmp, int max_length, t_map *m);

//test.c
void	test_parsing(t_map *m, int rows);
void	test_wall(t_map *m);

//wall_init.c
void	fill_var_map(int flag, char *ptr, t_map *m);
void	set_var_map(t_map *m, char *ptr);
void	free_walls(t_map *m);
char	*parse_walls(int fd, t_map *m);

//init_helpers.c
void	ft_prerr(char *str, char *argv);
int		zero_map_struct(t_map *m);
void	free_map_struct(t_map *m);
int		set_max_len(char *str, int max);
int		find_start_map(char *str);
int		check_all_arg(t_map *m);
void	free_map_struct2(t_map *m);

#endif