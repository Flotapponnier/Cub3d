#ifndef CUB3D_H
#define CUB3D_H

#include "MLX42.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define WIDTH 1280
#define HEIGHT 720

#define PI 3.14159265359
#define BLOCK 64
#define DEBUG 0

#define SIZE_PLAYER 10


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
//undraw
void clear_image(t_game *game);

//raycasting
bool touch(float px, float py, t_game *game);
#endif 
