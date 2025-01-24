#include "../../includes/cub3d.h"

void clear_image(t_game *game)
{
    if (!game->img || !game->img->pixels)
        return;
    ft_bzero(game->img->pixels, game->img->width * game->img->height * sizeof(int));
}
