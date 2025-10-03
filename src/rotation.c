#include "../include/header.h"

void rotate_right(t_cub *cub) {
  cub->player->dir = vec_rotate(cub->player->dir, -cub->player->rot_speed);
  cub->player->plane = vec_rotate(cub->player->plane, -cub->player->rot_speed);
}

void rotate_left(t_cub *cub) {
  cub->player->dir = vec_rotate(cub->player->dir, cub->player->rot_speed);
  cub->player->plane = vec_rotate(cub->player->plane, cub->player->rot_speed);
}
