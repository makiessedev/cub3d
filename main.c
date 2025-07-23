#include "include/header.h"

int main(void) {
  t_cub cub3d;

  init_cub(&cub3d);

  cub3d.player->dir = vec_rotate(cub3d.player->dir, 1.0);
  cub3d.player->plane = vec_rotate(cub3d.player->plane, 1.0);

  render_background(&cub3d);
  render_walls(&cub3d);

  mlx_put_image_to_window(cub3d.mlx, cub3d.win, cub3d.img_data.img, 0, 0);

  mlx_loop_hook(cub3d.mlx, &handle_no_event, &cub3d);

  mlx_loop(cub3d.mlx);

  return (0);
}
