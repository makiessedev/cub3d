NAME	= cub3D
CC		= cc
CFLAGS	= -Werror -Wextra -Wall

MLX_PATH	= mlx/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

SRC_PATH = ./src/
SRC		= 	main.c events.c \
						vec_operations.c rendering.c \
						print_error_and_exit.c moviments.c rotation.c \
						parser/handle_color.c parser/handle_texture.c \
						parser/map_parser.c parser/utils.c \
						parser/validation.c parser/utils2.c \
						parser/extract_elements.c parser/extract_map_utils.c \
						parser/validation_utils.c parser/check_cub_ext.c \
						utils.c utils2.c compute_wall.c \
						initialization/initialization.c initialization/initialization2.c \
						initialization/initialization3.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH	= ./objects/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

INC			=	-I ./includes/\
				-I ./libft/\
				-I ./minilibx-linux/

all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)parser
	mkdir -p $(OBJ_PATH)initialization

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm

$(LIBFT):
	make -sC $(LIBFT_PATH)

$(MLX):
	make -sC $(MLX_PATH)

clean:
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all re clean fclean
