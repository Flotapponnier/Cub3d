/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:15 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/02 15:36:46 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool is_valid_rgb(const char *color_str) 
{
    char **rgb;
    int r, g, b;
    bool valid = true;
    
    rgb = gc_add_split(color_str, ',');
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3]) {
        gc_free_ptr(rgb);
        return false;
    }
    
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		valid = false;

	gc_free_split(rgb);

	return valid;
}

static bool validate_texture_path(const char *path) 
{
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        close(fd);
        return false;
    }
    close(fd);

    // Check file extension is .png
    size_t len = ft_strlen(path);
    return (len > 4 && ft_strncmp(path + len - 4, ".png", 4) == 0);
}

static bool validate_map_textures_colors(t_map *map_struct)
{
    // Check if all textures and colors are present
    if (!map_struct->path_north || !map_struct->path_south || 
        !map_struct->path_west || !map_struct->path_east ||
        !map_struct->color_floor || !map_struct->color_cell)
        return false;

    // Validate texture paths
    if (!validate_texture_path(map_struct->path_north) ||
        !validate_texture_path(map_struct->path_south) ||
        !validate_texture_path(map_struct->path_west) ||
        !validate_texture_path(map_struct->path_east))
        return false;

    // Validate RGB colors
    if (!is_valid_rgb(map_struct->color_floor) ||
        !is_valid_rgb(map_struct->color_cell))
        return false;

    return true;
}

static bool is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == ' ' || c == 'N' || 
            c == 'S' || c == 'E' || c == 'W');
}

static bool check_surrounded_by_walls(char **map, int x, int y, t_game *game)
{
    if (x <= 0 || y <= 0 || x >= game->map_struct.map_width - 1 || 
        y >= game->map_struct.map_height - 1)
        return false;
    
    // Check if any adjacent space is out of bounds or empty
    if (y-1 < 0 || y+1 >= game->map_struct.map_height || 
        x-1 < 0 || x+1 >= (int)ft_strlen(map[y]))
        return false;

    // Check surrounding cells
    if (map[y-1][x] == ' ' || map[y+1][x] == ' ' || 
        map[y][x-1] == ' ' || map[y][x+1] == ' ')
        return false;

    return true;
}

static bool is_map_line(const char *line)
{
    while (*line)
    {
        if (*line != ' ' && *line != '1' && *line != '0' && 
            *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W')
            return false;
        line++;
    }
    return true;
}

static void set_player_direction(char c, t_player *player)
{
    if (c == 'N')
        player->angle = 3 * PI / 2;
    else if (c == 'S')
        player->angle = PI / 2;
    else if (c == 'W')
        player->angle = PI;
    else if (c == 'E')
        player->angle = 0;
}

static int validate_map_content(char **map, t_player *player, t_game *game)
{
    int player_count = 0;
    bool map_started = false;
    
    for (int y = 0; map[y]; y++) 
    {
        // Skip empty lines before map starts
        if (!map_started && ft_strlen(map[y]) == 0)
            continue;
            
        // If line contains map characters, map has started
        if (!map_started && is_map_line(map[y]))
            map_started = true;
            
        // Once map starts, no empty lines allowed
        if (map_started && ft_strlen(map[y]) == 0)
            return error("Map contains empty lines within map content");

        // Process valid map line    
        if (map_started)
        {
            for (int x = 0; map[y][x]; x++) 
            {
                if (!is_valid_map_char(map[y][x]))
                    return error("Invalid character in map");
                    
                if (ft_strchr("NSEW", map[y][x])) 
                {
                    player_count++;
                    if (player_count > 1)
                        return error("Multiple player positions found");
                        
                    player->x = x;
                    player->y = y;
                    set_player_direction(map[y][x], player);
                    
                    if (!check_surrounded_by_walls(map, x, y, game))
                        return error("Player position must be surrounded by walls");
                }
                else if (map[y][x] == '0' && !check_surrounded_by_walls(map, x, y, game))
                    return error("Found hole in map walls");
            }
        }
    }

    if (player_count == 0)
        return error("No player position found");
        
    return 0;
}

int check_map(t_map_node *map_list, t_player *player, t_game *game)
{
    // First validate textures and colors
    if (!validate_map_textures_colors(&game->map_struct))
        return error("Invalid textures or colors");

    // Convert linked list to array for easier processing
    char **map = get_map(map_list);
    if (!map)
        return error("Failed to process map");

    // Store map dimensions
    game->map_struct.map_height = 0;
    while (map[game->map_struct.map_height])
        game->map_struct.map_height++;
    
    game->map_struct.map_width = 0;
    for (int i = 0; map[i]; i++) {
        int len = ft_strlen(map[i]);
        if (len > game->map_struct.map_width)
            game->map_struct.map_width = len;
    }

    // Validate map content
    if (validate_map_content(map, player, game) != 0) {
        gc_free_ptr(map);
        return 1;
    }

    game->map = map;
    return 0;
}
