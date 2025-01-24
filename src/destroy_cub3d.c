#include "../includes/cub3d.h"

void	destroy_cub3d(int status)
{
	gc_close_fds();
	gc_free();
	exit(status);
}
