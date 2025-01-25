# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Imlx42/include -I./includes -g 

# Libraries
MLX_LIB = /Users/ftapponn/Documents/42/Cub3d/mlx42/build/libmlx42.a
LIBFT = ./libft/libft.a
GLFW_PATH = /Users/$(USER)/.brew/opt/glfw/lib
LDFLAGS = -L$(GLFW_PATH) -lglfw -framework Cocoa -framework OpenGL -framework IOKit

# Source files
SRC = src/main.c \
	  src/debug.c \
	  src/error/error.c \
	  src/initialising/game_init.c \
	  src/initialising/init_map.c \
	  src/initialising/check_map.c \
	  src/gcollector/gc_files.c \
	  src/gcollector/gc_list.c \
	  src/gcollector/gcollector.c \
	  src/destroy_cub3d.c \
	  src/game_draw/draw.c \
	  src/game_draw/draw_2d.c \
	  src/game_draw/draw_3d.c \
	  src/game_draw/undraw.c \
	  src/hook/key_hook.c \
	  src/game_player/game_player.c \
	  src/raycaster/raycasting.c \

# Object files
OBJ = $(SRC:.c=.o)

# Executable name
NAME = cub3d

# Build rule
all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) $(LIBFT) $(LDFLAGS) -o $(NAME)

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build libft
$(LIBFT):
	make -C ./libft

# Cleaning rules
clean:
	@rm -f $(OBJ)
	make clean -C ./libft

fclean: clean
	@rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
