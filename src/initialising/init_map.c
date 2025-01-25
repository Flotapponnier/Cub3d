#include "../../includes/cub3d.h"

int check_map(int fd)
{
    char *line;
    int i;
    int player_count = 0;

    while (1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            break;
        i = 0;
        while (line[i] != '\0')
        {
            if (line[i] == '1' || line[i] == '0' || line[i] == ' ' || line[i] == '\n')
                i++;
            else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
            {
                player_count++;
                if (player_count > 1)
                {
                    free(line);
                    return (error("More than one player on the map"));
                }
                i++;
            }
            else
            {
                free(line);
                return (error(ERROR_WRONG_CHAR));
            }
        }
        free(line);
    }
    if (player_count == 0)
        return (error("No player on the map"));
    return (0);
}


int init_map(t_game *game, char *path_user_input)
{
	(void)game;
	int fd;

	if (ft_strncmp(".cub", path_user_input + ft_strlen(path_user_input) - 4, 4) != 0)
		return (error(ERROR_EXTENSION) );
	fd = gc_add_fd(open(path_user_input, O_RDONLY)); 
	if (fd < 0)
		return (error(ERROR_FD));
	if(check_map(fd) == 1)
		return (1);
	return (0);;
}
