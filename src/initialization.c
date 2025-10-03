#include "../include/header.h"

void init_player(t_player *player) {
  player->dir.x = 0;
  player->dir.y = -1;

  player->plane.x = 0.66;
  player->plane.y = 0;

  player->move_speed = 0.009999;
  player->rot_speed = 0.009;
}

void init_cub(t_cub *cub) {
  cub->mlx = mlx_init();
  if (!cub->mlx) {
    ft_putendl_fd("Error to start MiniLibX\n", 2);
    exit(1);
  }
  cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Cub3D");
  if (!cub->win) {
    ft_putendl_fd("Error to open window", 2);
    exit(1);
  }
  cub->img_data.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
  if (!cub->img_data.img) {
    ft_putendl_fd("Error to create image", 2);
    exit(0);
  }
  cub->img_data.addr =
      mlx_get_data_addr(cub->img_data.img, &cub->img_data.bpp,
                        &cub->img_data.line_len, &cub->img_data.endian);
  if (!cub->img_data.addr) {
    ft_putendl_fd("Error to get addr", 2);
    exit(1);
  }
  if (!cub->player) {
    ft_putendl_fd("Allocation failure", 2);
    exit(1);
  }

  init_player(cub->player);
  load_all_textures(cub);
}
