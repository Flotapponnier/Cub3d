#ifndef CUB3D_H
#define CUB3D_H

#include "MLX42.h"
#include "libft.h"
#include "gcollector.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define WIDTH 1280
#define HEIGHT 720

#define PI 3.14159265359
#define BLOCK 64
#define DEBUG 0

#define ANGLE_SPEED 0.03
#define SPEED_PLAYER 3
#define SIZE_PLAYER 10

#define RAYCAST_COLOR 0x00FF0000FF
#define PLAYER_COLOR 0x000000FFFF
#define SQUARE2D_COLOR 0x00FFFF00FF
#define SQUARE3D_COLOR 0x00FFFF00FF

typedef struct s_player
{
	float angle;
	float x;
	float y;
	bool key_up;
	bool key_right;
	bool key_left;
	bool key_down;
	bool left_rotate;
	bool right_rotate;
}t_player;

typedef struct s_game
{
	void *mlx;

    mlx_image_t *img;
	int bpp;
	int size_line;
	int endian;
	t_player player;
	char **map;
}t_game;

//destroy
void	destroy_cub3d(mlx_t *mlx, int status);

//game init
void init_game(t_game *game);
void init_player(t_player *player);

//keyhook
void key_release(void *param);
void key_hook(struct mlx_key_data keydata, void *param);

//player
void move_player(t_player *player);
void move_player(t_player *player);

//draw
void draw_loop(void *param);
void draw_map(t_game *game);
void draw_square(int x, int y, int size, int color, t_game *game);
void draw_map(t_game *game);

//draw 2d
void draw_raycast_line(mlx_image_t *img, uint32_t ray_x, uint32_t ray_y, uint32_t color);

//draw 3d
void draw_wall_3d(t_game *game, uint32_t i, uint32_t ray_x, uint32_t ray_y, t_player *player);


//undraw
void clear_image(t_game *game);

//raycasting
float fixed_distance(float x1, float y1, float x2, float y2, t_game *game);

//debug
void print_debug_info(t_game *game);
#endif 

