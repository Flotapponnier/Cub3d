#include "../includes/cub3d.h"

void print_debug_info(t_game *game)
{
    t_player *player = &game->player;
    printf("===== DEBUG INFO =====\n");
    printf("Player Position: (%.2f, %.2f)\n", player->x, player->y);
    
    int gridX = (int)(player->x / BLOCK);
    int gridY = (int)(player->y / BLOCK);
    printf("Grid Position: (%d, %d)\n", gridX, gridY);
    
    // Check if gridY is within map bounds
    int rows = 0;
    while (game->map[rows] != NULL)
        rows++;
    
    if (gridY >= 0 && gridY < rows) {
        int cols = strlen(game->map[gridY]);
        if (gridX >= 0 && gridX < cols) {
            printf("Current Cell: %c\n", game->map[gridY][gridX]);
        } else {
            printf("Current Cell: X out of bounds (GridX: %d, Map Columns: %d)\n", gridX, cols);
        }
    } else {
        printf("Current Cell: Y out of bounds (GridY: %d, Map Rows: %d)\n", gridY, rows);
    }
    
    // Player angle in radians and degrees
    float angle_deg = player->angle * (180.0 / PI);
    printf("Player Angle: %.2f radians (%.2f degrees)\n", player->angle, angle_deg);
    
    // Movement and rotation keys
    printf("Movement Keys:\n");
    printf("W (Up): %s\n", player->key_up ? "Pressed" : "Released");
    printf("S (Down): %s\n", player->key_down ? "Pressed" : "Released");
    printf("A (Left): %s\n", player->key_left ? "Pressed" : "Released");
    printf("D (Right): %s\n", player->key_right ? "Pressed" : "Released");
    printf("Left Rotate: %s\n", player->left_rotate ? "Pressed" : "Released");
    printf("Right Rotate: %s\n", player->right_rotate ? "Pressed" : "Released");
    
    // Map dimensions
    rows = 0;
    while (game->map[rows] != NULL)
        rows++;
    printf("Map Dimensions: %d rows\n", rows);
    if (rows > 0) {
        int cols = strlen(game->map[0]);
        printf("First row length: %d columns\n", cols);
    }
    
    // Nearby map cells (5x5 grid around player's grid position)
    printf("\nNearby Map Cells (5x5 grid around player):\n");
    int startY = gridY - 2;
    int endY = gridY + 2;
    int startX = gridX - 2;
    int endX = gridX + 2;
    
    for (int y = startY; y <= endY; y++) {
        if (y < 0 || y >= rows) {
            printf("Row %d: Out of bounds\n", y);
            continue;
        }
        int cols = strlen(game->map[y]);
        printf("Row %2d: ", y);
        for (int x = startX; x <= endX; x++) {
            if (x < 0 || x >= cols) {
                printf("  ");
            } else {
                printf("%c ", game->map[y][x]);
            }
        }
        printf("\n");
    }
    printf("===== END DEBUG INFO =====\n\n");
}

void print_map(char **map)
{
    int i = 0;

    if (!map)
    {
        printf("Map is NULL\n");
        return;
    }

    while (map[i])
    {
        printf("%s\n", map[i]);
        i++;
    }
}
