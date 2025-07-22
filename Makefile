NAME = cub
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRC_DIR		= src
INC_DIR		= include
MLX_DIR		= mlx
LIBFT_DIR	= libft

MLX_LIB		= $(MLX_DIR)/libmlx.a
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

SRCS		= main.c $(wildcard $(SRC_DIR)/*.c)
OBJS		= $(SRCS:.c=.o)

INCLUDES	= -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)


MLX_FLAGS = -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) -L$(MLX_DIR) -lmlx $(MLX_FLAGS) -L$(LIBFT_DIR) -lft

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean || true

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
