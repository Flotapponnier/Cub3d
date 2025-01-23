#include "../../includes/cub3d.h"


void	move_player(t_player *player)
{
	int		speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	angle_speed = 0.1;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	speed = 5;

	// Rotation handling remains the same
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;

	// Forward/backward movement (W/S keys) - correct
	if (player->key_up)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->key_down)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}

	// Left/right strafing (A/D keys) - corrected
	if (player->key_left)
	{
		// Strafe left: move perpendicular to facing direction (-sinθ, cosθ)
		player->x += -sin_angle * speed;
		player->y += cos_angle * speed;
	}
	if (player->key_right)
	{
		// Strafe right: move perpendicular to facing direction (sinθ, -cosθ)
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
}
