#include "include/header.h"

int main_loop(t_cub *cub) {
  handle_input(cub);
  render_background(cub);
  render_walls(cub);

  mlx_put_image_to_window(cub->mlx, cub->win, cub->img_data.img, 0, 0);
  return (0);
}

int main(int ac, char **av) {
  t_cub *cub = malloc(sizeof(t_cub));
  cub->map = malloc(sizeof(t_map));
  cub->player = ft_calloc(1, sizeof(t_player));
  cub->ray = malloc(sizeof(t_ray));

  if (ac != 2) {
    ft_putendl_fd("Error", 2);
    return (1);
  }

  if (parser_map(cub, av[1]) == false) {
    ft_putendl_fd("Error", 2);
    return (1);
  }

  init_cub(cub);

  cub->player->dir = vec_rotate(cub->player->dir, 0);
  cub->player->plane = vec_rotate(cub->player->plane, 0);

  mlx_loop_hook(cub->mlx, &main_loop, cub);
  mlx_hook(cub->win, DESTROY_NOTIFY, IGNORE_MASK, &game_exit, cub);
  mlx_hook(cub->win, KEYPRESS, KEYPRESS_MASK, &handle_keypress, cub);
  mlx_hook(cub->win, KEYRELEASE, KEYRELEASE_MASK, &handle_keyrelease, cub);

  mlx_loop(cub->mlx);

  return (0);
}
