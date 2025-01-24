# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Imlx42/include -I./includes -g 

MLX_LIB = /Users/ftapponn/Documents/42/Cub3d/mlx42/build/libmlx42.a
SRC = src/main.c \
	  src/game_init.c \
	  src/game_draw/draw.c \
	  src/game_draw/draw_2d.c \
	  src/game_draw/draw_3d.c \
	  src/game_draw/undraw.c \
	  src/hook/key_hook.c \
	  src/game_player/game_player.c \
	  src/raycaster/raycasting.c \

OBJ = $(SRC:.c=.o)
LIBFT = ./libft/libft.a
NAME = cub3d

GLFW_PATH = /Users/$(USER)/.brew/opt/glfw/lib
LDFLAGS = -L$(GLFW_PATH) -lglfw -framework Cocoa -framework OpenGL -framework IOKit

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C ./libft

clean:
	@rm -f $(OBJ)
	make clean -C ./libft

fclean: clean
	@rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
