#include "../../includes/cub3d.h"

int init_map(t_game *game, char *path_user_input)
{
	(void)game;
	if (ft_strncmp(".cub", path_user_input + ft_strlen(path_user_input) - 4, 4) != 0)
		return (error(ERROR_EXTENSION) );
	return (0);;
}
