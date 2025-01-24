#include "../../includes/cub3d.h"

void draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->x;
	float ray_y = player->y;

	while(!touch(ray_x, ray_y, game))
	{
		if(DEBUG)
			draw_raycast_line(game->img, (int)ray_x, (int)ray_y, 0x00FF00FF);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if(!DEBUG)
    	draw_wall_3d(game, i, ray_x, ray_y, player);
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
	if(DEBUG)
	{
		draw_square(player->x, player->y, SIZE_PLAYER, 0x00FF00FF, game);
		draw_map(game);
	}
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
