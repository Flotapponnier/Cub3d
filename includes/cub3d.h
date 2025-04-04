/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:42:34 by dilin             #+#    #+#             */
/*   Updated: 2025/02/04 09:17:34 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "errno.h"
# include "libft.h"
# include "gcollector.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define RED "\033[31m"
# define RESET "\033[0m"

# define WIDTH 1280
# define HEIGHT 720

# define PI 3.14159265359
# define BLOCK 64

# define ANGLE_SPEED 0.05
# define SPEED_PLAYER 3
# define SIZE_PLAYER 10
# define SPACE_COLLISION 10

# define RAYCAST_COLOR 0x00FF0000FF
# define PLAYER_COLOR 0x000000FFFF
# define SQUARE2D_COLOR 0x00FFFF00FF

# define ERROR_ARG "argument should be ./cub3d maps/correct/nameofmap"
# define ERROR_EXTENSION "file should be a .cub file"
# define ERROR_FD "Can't find file"
# define ERROR_WRONG_CHAR "Map contains wrong character"

typedef struct s_queue
{
	int					x;
	int					y;
	struct s_queue		*next;
}						t_queue;

typedef struct s_map_node
{
	char				*line;
	struct s_map_node	*next;
}						t_map_node;

typedef struct s_player
{
	float				angle;
	float				x;
	float				y;
	bool				key_up;
	bool				key_right;
	bool				key_left;
	bool				key_down;
	bool				left_rotate;
	bool				right_rotate;
}						t_player;

typedef struct s_map
{
	char				**map;
	int					map_height;
	int					map_width;
	char				*path_north;
	char				*path_south;
	char				*path_west;
	char				*path_east;
	char				*color_floor;
	char				*color_cell;
}						t_map;

typedef struct s_map_data
{
	char				**map;
	int					width;
	int					height;
	bool				**visited;
}						t_map_data;

typedef struct s_pos
{
	int					x;
	int					y;
}						t_pos;

typedef struct s_angle
{
	float				sin;
	float				cos;
}						t_angle;

typedef struct s_ray
{
	double				camera_x;
	double				dir_x;
	double				dir_y;
	double				ray_dir_x;
	double				ray_dir_y;
	int					map_x;
	int					map_y;
	double				delta_dist_x;
	double				delta_dist_y;
	int					step_x;
	int					step_y;
	double				side_dist_x;
	double				side_dist_y;
	int					side;
	int					line_height;
	int					draw_start;
	int					draw_end;
	char				direction;
	double				distance_to_wall;
}						t_ray;

typedef struct s_draw_params
{
	double				perp_wall_dist;
	int					line_height;
	int					draw_start;
	int					draw_end;
	double				wall_x;
	int					tex_num;
}						t_draw_params;

typedef struct s_texture
{
	mlx_texture_t		*texture;
	uint32_t			*pixels;
	int					width;
	int					height;
}						t_texture;

typedef struct s_game
{
	void				*mlx;
	mlx_image_t			*img;
	t_map				map_struct;
	t_ray				ray;
	char				**map;
	int					bpp;
	int					size_line;
	int					endian;
	t_player			player;
	t_texture			textures[4];
	uint32_t			floor_color;
	uint32_t			ceiling_color;
	bool				debug_view;
}						t_game;

typedef struct s_map_validator
{
	t_game				*game;
	t_player			*player;
	int					*player_count;
	char				**map;
}						t_map_validator;

typedef struct s_line
{
	int					dx;
	int					dy;
	int					sx;
	int					sy;
	int					err;
	int					e2;
	int					x1;
	int					y1;
	int					x2;
	int					y2;
}						t_line;

typedef struct s_line_params
{
	int					end_x;
	int					end_y;
	int					color;
}						t_line_params;

typedef struct s_line_coord
{
	int					start_x;
	int					start_y;
	int					end_x;
	int					end_y;
}						t_line_coord;

typedef struct s_square_params
{
	int					x;
	int					y;
	int					size;
	int					color;
}						t_square_params;

// destroy
void					destroy_cub3d(mlx_t *mlx, int status);

// game init
int						init_game(t_game *game, char *path_user_input);
void					init_player(t_player *player);

// checkmap
int						check_map(t_map_node *map_list, t_player *player,
							t_game *game);

// flood_fill
bool					flood_fill(char **map, int width, int height,
							t_pos start);

// map init
int						init_map(t_game *game, char *path_user_input);
void					free_map_list(t_map_node *map_list);
char					**get_map(t_map_node *map_list);
char					**store_map(char **new_map);

// keyhook
void					key_hook(struct mlx_key_data keydata, void *param);

// player
void					move_player(t_player *player, char **map);

// draw
void					draw_loop(void *param);
void					draw_map(t_game *game);
void					draw_square(t_square_params params, t_game *game);
void					draw_map(t_game *game);

// draw 2d
void					draw_line(int start_x, int start_y,
							t_line_params *params, t_game *game);

// draw 3d
void					draw_floor_slice(t_game *game, int i, int start_y);
void					draw_ceiling_slice(t_game *game, int i,
							int ceiling_end);
void					draw_3d_monitor(t_game *game, int x);

// undraw
void					clear_image(t_game *game);

// raycasting
void					cast_ray(t_game *game, t_ray *ray, int x);

// debug
// void print_debug_info(t_game *game);
void					print_map(char **map);

// error
int						error(const char *msg);

// texture
int						load_all_textures(t_game *game);
void					free_textures(t_game *game);
uint32_t				get_texture_color(t_texture *tex, float tex_x,
							float tex_y);

// unsorted (I'm lazy)
uint32_t				convert_rgb_to_uint(char *color_str);
int						process_map_data(t_game *game, t_map_node *map_list);
t_map_node				*load_map(int fd);
int						process_map_line(char *line, int y,
							t_map_validator *ctx);
int						process_map_metadata(t_map *map_struct, char *line);
bool					is_map_line(const char *line);
bool					validate_map_textures_colors(t_map *map_struct);
void					enqueue(t_queue **queue, int x, int y);
void					dequeue(t_queue **queue);
bool					check_player_position(char c, int x, int y,
							t_map_validator *ctx);
bool					check_surrounded_by_walls(char **map, int x, int y,
							t_game *game);
void					clean_newline(char *str);
int						count_map_lines(t_map_node *map_list);
double					calculate_wall_distance(t_ray *ray, t_player *player);
void					calculate_draw_params(double perp_wall_dist,
							int *draw_start,
							int *draw_end,
							int *line_height);
void					calculate_wall_texture(t_game *game,
							double perp_wall_dist,
							double *wall_x,
							int *tex_num);
void					handle_forward(t_player *player, float cos_angle,
							float sin_angle, char **map);
void					handle_backward(t_player *player, float cos_angle,
							float sin_angle, char **map);
void					handle_strafe_direction(t_player *player, t_angle angle,
							int direction, char **map);
void					update_position(t_player *player, float new_x,
							float new_y, char **map);
bool					process_pre_map_line(char *line, bool *map_started);
void					free_map(char **map);
#endif
