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

#define W 119
#define A 97
#define S 115
#define D 100
#define PI 3.14159265359


typedef struct s_player
{
	float x;
	float y;
	bool key_up;
	bool key_right;
	bool key_left;
	bool key_down;
}t_player;

typedef struct s_game
{
	void *mlx;

    mlx_image_t *img;        // Change img to be a pointer to mlx_image_t
	int bpp;
	int size_line;
	int endian;
	t_player player;
}t_game;

void draw_square(int x, int y, int size, int color, t_game *game);
void init_game(t_game *game);
void init_player(t_player *player);
void key_release(void *param);
void move_player(t_player *player);
void key_hook(struct mlx_key_data keydata, void *param);
void move_player(t_player *player);
#endif 
