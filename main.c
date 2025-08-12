#include "include/header.h"
#include <stdlib.h>

void print_elements(t_cub *cub) {
  t_map *map = cub->map;
  printf("NO - %s\n", map->NO);
  printf("SO - %s\n", map->SO);
  printf("WE - %s\n", map->WE);
  printf("EA - %s\n", map->EA);

  printf("\n------------------------------------------\n");

  for (int i = 0; i < 3; i++) {
    printf("F %s\n", map->F[i]);
  }

  for (int i = 0; i < 3; i++) {
    printf("C %s\n", map->C[i]);
  }

  printf("\n------------------------------------------\n");

  for (int i = 0; map->gamemap[i]; i++) {
    printf("%s\n", map->gamemap[i]);
  }
}

int main(int ac, char **av) {
  t_cub *cub = malloc(sizeof(t_cub));
  cub->map = malloc(sizeof(t_map));
  cub->player = ft_calloc(1, sizeof(t_player));

  if (ac != 2) {
    ft_putendl_fd("Error", 2);
    return (1);
  }

  if (parser_map(cub, av[1]) == false) {
    ft_putendl_fd("Error", 2);
    return (1);
  }

  init_cub(cub);

  print_elements(cub);

  cub->player->dir = vec_rotate(cub->player->dir, 0);
  cub->player->plane = vec_rotate(cub->player->plane, 0);

  mlx_loop_hook(cub->mlx, &main_loop, cub);
  mlx_hook(cub->win, KEYPRESS, KEYPRESS_MASK, &handle_keypress, cub);
  mlx_hook(cub->win, DESTROY_NOTIFY, IGNORE_MASK, &game_exit, cub);

  mlx_loop(cub->mlx);

  return (0);
}
