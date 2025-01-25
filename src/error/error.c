#include "../../includes/cub3d.h"

int error(const char *msg)
{
    write(2, RED "Error: ", 12);
    write(2, msg, ft_strlen(msg));
    write(2, RESET "\n", 1);
    return (1);
}
