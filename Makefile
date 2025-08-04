NAME			= cub3D
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g
MLX_FLAGS = -lX11 -lXext -lm

SRC_PATH		= src/
OBJ_PATH		= obj/
INC_PATH		= include/
MLX_DIR			= mlx/
LIBFT_DIR		= libft/

MLX_LIB			= $(MLX_DIR)libmlx.a
LIBFT_LIB		= $(LIBFT_DIR)libft.a

# Arquivos fonte
SRCS_ROOT		= main.c
SRCS_FROM_DIR	= ./src/events.c ./src/initialization.c \
						./src/map_parser.c ./src/vec_operations.c ./src/rendering.c \
						./src/textures.c
SRCS			= $(SRCS_ROOT) $(SRCS_FROM_DIR)

# Objetos
OBJS_ROOT		= $(patsubst %.c, $(OBJ_PATH)%.o, $(SRCS_ROOT))
OBJS_FROM_DIR	= $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRCS_FROM_DIR))
OBJS			= $(OBJS_ROOT) $(OBJS_FROM_DIR)

INCLUDES		= -I$(INC_PATH) -I$(MLX_DIR) -I$(LIBFT_DIR)

all: $(OBJ_PATH) $(LIBFT_LIB) $(MLX_LIB) $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(shell find $(SRC_PATH) -type d | sed "s|$(SRC_PATH)|$(OBJ_PATH)|")

# Regra de compilação para arquivos em src/
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

# Regra de compilação para arquivos no diretório raiz
$(OBJ_PATH)%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCLUDES) -L$(MLX_DIR) -lmlx $(MLX_FLAGS) -L$(LIBFT_DIR) -lft

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_PATH)
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
