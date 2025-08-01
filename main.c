#include "include/header.h"

int main(int ac, char **av) {
  t_cub cub;

  if (ac != 2) {
    ft_putendl_fd("Error", 2);
    return (1);
  }

  if (parser_map(&cub, av[1]) == false) {
    ft_putendl_fd("Error", 2);
    return (1);
  }
  init_cub(&cub);

  cub.player->dir = vec_rotate(cub.player->dir, 1.0);
  cub.player->plane = vec_rotate(cub.player->plane, 1.0);

  mlx_loop_hook(cub.mlx, &main_loop, &cub);
  mlx_hook(cub.win, KEYPRESS, KEYPRESS_MASK, &handle_keypress, &cub);
  mlx_hook(cub.win, DESTROY_NOTIFY, IGNORE_MASK, &game_exit, &cub);

  mlx_loop(cub.mlx);

  return (0);
}

