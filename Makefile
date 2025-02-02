# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Imlx42/include -I./includes -g 

# Libraries
MLX_LIB = ./MLX42/build/libmlx42.a
LIBFT = ./libft/libft.a
GLFW_PATH = /Users/$(USER)/.brew/opt/glfw/lib
LDFLAGS = -L$(GLFW_PATH) -lglfw -framework Cocoa -framework OpenGL -framework IOKit

# Directories
OBJ_DIR = obj

# Source files
SRC = src/main.c \
	  src/debug.c \
	  src/error/error.c \
	  src/initialising/game_init.c \
	  src/initialising/init_map.c \
	  src/initialising/check_map.c \
	  src/initialising/flood_fill.c \
	  src/initialising/map_char_validator.c \
	  src/initialising/map_texture_validator.c \
	  src/initialising/player_validator.c \
	  src/initialising/queue_operations.c \
	  src/initialising/map_array.c \
	  src/initialising/map_node.c \
	  src/initialising/map_rgb.c \
	  src/initialising/map_validation.c \
	  src/gcollector/gc_files.c \
	  src/gcollector/gc_list.c \
	  src/gcollector/gcollector.c \
	  src/destroy_cub3d.c \
	  src/game_draw/draw.c \
	  src/game_draw/draw_2d.c \
	  src/game_draw/draw_2d_line.c \
	  src/game_draw/draw_3d.c \
	  src/game_draw/draw_3d_calc.c \
	  src/game_draw/undraw.c \
	  src/hook/key_hook.c \
	  src/game_player/game_player.c \
	  src/game_player/player_collision.c \
	  src/game_player/player_movement.c \
	  src/raycaster/raycasting.c \
	  src/textures.c \
	  src/textures_utils.c \

# Object files
OBJ = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Executable name
NAME = cub3D

# Build rule
all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) $(LIBFT) $(LDFLAGS) -o $(NAME)

# Create necessary directories and compile .c files into .o files
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build libft
$(LIBFT):
	make -C ./libft

# Cleaning rules
clean:
	@rm -rf $(OBJ_DIR)
	make clean -C ./libft

fclean: clean
	@rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
