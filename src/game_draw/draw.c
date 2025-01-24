#include "../../includes/cub3d.h"

void draw_map(t_game *game)
{
    char **map = game->map;
    int color = 0x0000FF00FF;
    for(int y = 0; map[y]; y++)
        for(int x = 0; map[y][x]; x++)
            if(map[y][x] == '1')
                draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
}

float distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

void draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->x;
	float ray_y = player->y;
	float dist;
	float height;
	int start_y;
	int end;
	
	while(!touch(ray_x, ray_y, game))
	{
		//mlx_put_pixel(game->img, (int)ray_x, (int)ray_y, 0x00FF00FF);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	dist = distance(ray_x - player->x, ray_y - player->y);
	if (dist <= 0)
	    dist = 0.0001f;
	height = (BLOCK / dist) * ((float)WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	if(end >= HEIGHT)
		end = HEIGHT - 1;
	while(start_y < end)
	{
		mlx_put_pixel(game->img, (int)i, (int)start_y, 0x00FF00FF);
		start_y++;
	}
}

void draw_loop(void *param)
{
    t_game *game = (t_game *)param;
    t_player *player = &game->player;
	float fraction;
	float start_x;
	int i;

	player = &game->player;
	move_player(player);
	clear_image(game);
	//draw_square(player->x, player->y, SIZE_PLAYER, 0x00FF00FF, game);
	//draw_map(game);

	
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;	
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
	int i = -1;
	
	while (++i < size)
		mlx_put_pixel(game->img, x + i, y, color);
	i = - 1;
	while (++i < size)
		mlx_put_pixel(game->img, x, y + i, color);
	i = -1;
	while (++i < size)
		mlx_put_pixel(game->img, x + size, y + i, color);
	i = -1;
	while (++i < size)
		mlx_put_pixel(game->img, x + i, y + size, color);
}
