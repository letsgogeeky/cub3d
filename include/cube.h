#ifndef CUBE_H
# define CUBE_H

# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "MLX42/MLX42.h"
# include "baselib.h"
# include <stdbool.h>
# include <math.h>

# define WIDTH 1366
# define HEIGHT 768

# define AMOUNT_RAYS_2D_FOV 10

# define STRUCT_FAILED "building of struct failed"
# define INV_MAP "invalid map"
# define PARSING_MAP_FAILED "parsing of the input map failed"
# define INV_FD "invalid file descriptor"
# define PARSING_FAILED "parsing failed"
# define WRONG_ARG "wrong amount of arguments entered"
# define CUB_FORMAT "input file needs .cub format"
# define INV_TEX_FILE "texture file included in map is invalid"
# define FAIL_GAME_INIT "Error: failed to initialize game\n"
# define FAIL_DOORS_INIT "Error: failed to initialize doors\n"

# define MINIMAP_PLAYER 0x34A853FF
# define MINIMAP_WALL 0x4285F4FF
# define MINIMAP_FLOOR 0xFBBC05FF
# define MINIMAP_DIR 0xEA4335FF
# define MINIMAP_DOOR 0x7C3F00FF

typedef struct s_position
{
	double	x;
	double	y;
}		t_position;

typedef struct s_position_int
{
	int	x;
	int	y;
}		t_position_int;


typedef struct s_texture
{
	char			*path;
	mlx_texture_t	*tex;
}		t_texture;

typedef struct s_color
{
	char	*str_color;
	int		red;
	int		green;
	int		blue;
	int		hex_color_rgb;
}		t_color;

typedef struct s_door
{
	t_position_int		pos;
	bool				is_open;
}		t_door;

typedef struct s_map // every element is allocated and has to be freed if failure occures
{
	t_texture			*north_texture;
	t_texture			*south_texture;
	t_texture			*west_texture;
	t_texture			*east_texture;
	t_texture			*door_texture;
	t_color				*floor_color;
	t_color				*ceiling_color;
	char				**map;
	int					rows;
	int					cols;
	t_door				*doors;
	int					doors_count;
}		t_map;


enum e_symbol
{
	EMPTY = ' ',
	WALL = '1',
	SPACE = '0',
	DOOR = 'D',
};

enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	UNKNOWN,
};

typedef struct	s_vector
{
	double	x;
	double	y;
}		t_vector;

typedef struct s_column
{
	int	end_ceiling;
	int	start_floor;
	int	wall_height;
}		t_column;

typedef struct s_ray
{
	t_vector			dir;
	t_vector			angle;
	t_vector			step_for_plus_x;
	t_vector			step_for_plus_y;
	t_vector			hitpoint;
	t_vector			side_dist_x;
	t_vector			side_dist_y;
	t_vector			delta_dist;
	t_vector			map;
	double				len_to_wall;
	double				len_to_plane;
	double				wall_height;
	enum e_direction	wall_texture;
}		t_ray;

typedef struct	s_player
{
	t_position			pos;
	t_position			coordinate;
	t_vector			dir;
	t_vector			plane;
	double				rotation_angle;
	double				walk_speed;
	double				turn_speed;
	enum e_direction	init_orientation;
}		t_player;

typedef struct s_data
{
	t_player	player;
	t_ray		*rays;
}		t_data;

typedef struct s_minimap
{
	int			width;
	int			height;
	mlx_image_t	*image;
	int			arrows_count;
	double		p_radius;
}		t_minimap;

typedef struct s_game
{
	t_map		*map;
	t_player	player;
	t_ray		ray;
	// t_data		*data;
	int			block_size;
	mlx_image_t	*image;
	t_minimap	*minimap;
	mlx_t		*mlx;
}		t_game;

int			validate(t_map *map);

//draw_3d.c
void		draw_ceiling(t_game *game, t_column *column, int x);
void		draw_floor(t_game *game, t_column *column, int x);
void		draw_image(t_game *game, t_column *column, int x);
void		draw_column(t_game *game, t_column *column, int x);

//calc_3d.c
t_column	calculate_height(t_game *game);
void		calculate_length_to_plane(t_game *game);

//image.c
void		load_textures(t_map *map);
mlx_texture_t	*choose_texture(t_game *game);
int			find_color(mlx_texture_t *txt, double x, double y);
int			interpolate(mlx_texture_t *txt, double col, double y);
void		resze_tex(mlx_texture_t *normal, t_game *game, t_column *column, int x);

//draw_2d.c
void		draw_line(t_game *game, t_vector start, t_vector end, int color);
void		draw_ray(t_game *game, int color);

//set_var.c
double		vector_length(t_vector *vec);
void		add_one_step(t_vector *side_dist, t_vector *step);
void		set_hitpoint(t_position *hitpoint, t_game *game, int i);
void		set_steps(t_game *game);
void		set_angle(t_game *game, int x, int amnt_ray);

//set_var_2.c
t_vector	set_player_in_block(t_game *game);
t_vector	set_first_block_border(t_game *game);
void		set_wall_direction(t_vector *vector, int version, t_game *game);

//calc_ray.c
void		set_dda(t_position *hitpoint, t_game *game, t_vector *d, int version);
void		dda(t_position *hitpoint, t_game *game, t_vector *dx, t_vector *dy);
void		calculate_hitpoint(t_game *game);

// check_ray.c
int			check_first_wall(t_game *game, t_vector factor, t_position *hitpoint);
int			check_hit(t_game *game, t_position hitpoint);

// cast.c
t_ray		init_ray(void);
void		visualize_2d_ray(t_game *game, int color);
void		visualize_3d(t_game *game);

//init.c
t_game		*allocate_game(t_map *m);
t_game		*init_game(t_map *m);
// void		ft_keyhook(mlx_key_data_t keydata, void *param);
void		ft_hook(void *param);
void		free_game(t_game *game);
void		open_n_draw(t_map *m);

//map_init.c
void		set_char(int i, char *tmp, int max_length, t_map *m);
int			fill_map(t_map *m, int fd, int rows, int max_length);
int			parse_map(int fd, t_map *m, char *tmp, char *argv);
t_map		*parse(t_map *m, int fd, char *argv);

//wall_init.c
void		fill_var_map(int flag, char *ptr, t_map *m);
void		set_var_map(t_map *m, char *ptr);
int			fill_color_struct(t_color *c);
void		adjust_wall_path(t_map *m);
char		*parse_walls(int fd, t_map *m);

//init_helpers.c
void		ft_prerr(char *str, char *argv);
int			zero_map_struct(t_map *m);
int			set_max_len(char *str, int max);
int			find_start_map(char *str);
int			colorcode(int red, int green, int blue);

//free.c
void		free_s_texture(t_texture *t);
void		free_string(char *str);
void		free_color(t_color *c);
void		free_walls(t_map *m);
void		free_map_struct(t_map *m);
void		free_game(t_game *game);

//check.c
void		check_n_change_c(char *str);
int			check_end(char *str);
int			check_path(t_map *m);
int			check_all_arg(t_map *m);

//test.c
void		test_parsing(t_map *m, int rows);
void		test_wall(t_map *m);

//draw.c
void		fill_block(t_game *game, int x, int y, int color);
void		draw_vert(t_game *game, int block_size);
void		draw_hor(t_game *game, int block_size);
void		draw_block(t_game *game);

//graphics
void	clear_image(mlx_image_t *image, int width, int height);

// player
t_player	init_player(t_map *map);
t_ray		init_ray(void);
void		visualize_2d_ray(t_game *game, int color);
enum e_direction	get_orientation(char c);
bool		is_orientation(char c);
t_position	get_player_position(t_map *map);
void		log_player_position(t_map *map);
char		*direction_to_str(enum e_direction direction);
void		show_player(t_game *game);
bool		player_collision(t_game *game, t_position point, int radius);
bool		player_inside_door(t_game *game, t_position point, int radius);

// movement
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate(t_game *game, bool clockwise);
void	do_raycast(t_game *game);

// doors
int		doors_count(t_map *map);
bool	door_is_open(t_game *game, int x, int y);
void	door_open_close(t_game *game, int x, int y);
void	door_control(t_game *game);

// math_utils
double	sqrt_xy_squared(double x, double y);
t_vector	rotate_vector(t_vector vec, double angle);
#endif
