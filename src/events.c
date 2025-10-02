#include "../include/header.h"

int game_exit(t_cub *cub) {
  (void)cub;
  exit(0);
  return (0);
}

bool is_border_wall(t_cub *cub, int mapX, int mapY) {
  int map_height = cub->map->height;
  int map_width = cub->map->width;

  if (mapY == 0 || mapY == map_height - 1 || mapX == 0 ||
      mapX == map_width - 1) {
    return (true);
  }
  return (false);
}

bool newpos_isvalid(t_cub *cub, float new_posX, float new_posY) {
  int new_mapX = (int)new_posX;
  int new_mapY = (int)new_posY;
  char tile = cub->map->gamemap[new_mapY][new_mapX];

  if (!(tile == '1' && is_border_wall(cub, new_mapX, new_mapY)))
    return true;

  return false;
}

int main_loop(t_cub *cub) {

  if (cub->key_status.ESC_PRESSED == true) {
    exit(0);
  }

  // Movimento para frente (W ou Seta para Cima)
  if (cub->key_status.MOVE_UP_PRESSED == true ||
      cub->key_status.MOVE_UP2_PRESSED == true) {

    float new_posX =
        cub->player->pos.x + cub->player->dir.x * cub->player->move_speed;
    float new_posY =
        cub->player->pos.y + cub->player->dir.y * cub->player->move_speed;

    if (newpos_isvalid(cub, new_posX, cub->player->pos.y))
      cub->player->pos.x = new_posX;

    if (newpos_isvalid(cub, cub->player->pos.x, new_posY))
      cub->player->pos.y = new_posY;
  }

  // Movimento para trás (S ou Seta para Baixo)
  if (cub->key_status.MOVE_DOWN_PRESSED == true ||
      cub->key_status.MOVE_DOWN2_PRESSED == true) {
    float new_posX =
        cub->player->pos.x - cub->player->dir.x * cub->player->move_speed;
    float new_posY =
        cub->player->pos.y - cub->player->dir.y * cub->player->move_speed;

    if (newpos_isvalid(cub, new_posX, cub->player->pos.y))
      cub->player->pos.x = new_posX;

    if (newpos_isvalid(cub, cub->player->pos.x, new_posY))
      cub->player->pos.y = new_posY;
  }

  // Mover para a direita (D)
  if (cub->key_status.MOVE_RIGHT_PRESSED == true) {
    float new_posX =
        cub->player->pos.x + cub->player->plane.x * cub->player->move_speed;
    float new_posY =
        cub->player->pos.y + cub->player->plane.y * cub->player->move_speed;

    if (newpos_isvalid(cub, new_posX, cub->player->pos.y))
      cub->player->pos.x = new_posX;
    if (newpos_isvalid(cub, cub->player->pos.x, new_posY))
      cub->player->pos.y = new_posY;
  }

  // Mover para a esquerda (A) - usando o vetor do plano da câmera
  if (cub->key_status.MOVE_LEFT_PRESSED == true) {
    float new_posX =
        cub->player->pos.x - cub->player->plane.x * cub->player->move_speed;
    float new_posY =
        cub->player->pos.y - cub->player->plane.y * cub->player->move_speed;

    if (newpos_isvalid(cub, new_posX, cub->player->pos.y))
      cub->player->pos.x = new_posX;
    if (newpos_isvalid(cub, cub->player->pos.x, new_posY))
      cub->player->pos.y = new_posY;
  }

  // Rotacionar para a direita (Seta para Direita)
  if (cub->key_status.ROTATE_RIGHT_PRESSED == true) {
    cub->player->dir = vec_rotate(cub->player->dir, -cub->player->rot_speed);
    cub->player->plane =
        vec_rotate(cub->player->plane, -cub->player->rot_speed);
  }

  // Rotacionar para a esquerda (Seta para Esquerda)
  if (cub->key_status.ROTATE_LEFT_PRESSED == true) {
    cub->player->dir = vec_rotate(cub->player->dir, cub->player->rot_speed);
    cub->player->plane = vec_rotate(cub->player->plane, cub->player->rot_speed);
  }

  render_background(cub);
  render_walls(cub);

  mlx_put_image_to_window(cub->mlx, cub->win, cub->img_data.img, 0, 0);
  // mlx_destroy_image(cub->mlx, cub->img_data.img);

  return (0);
}

int handle_keypress(int keycode, void *cub3d_ptr) {
  t_cub *cub3d = (t_cub *)cub3d_ptr;

  if (keycode == ESC)
    cub3d->key_status.ESC_PRESSED = true;
  if (keycode == MOVE_UP)
    cub3d->key_status.MOVE_UP_PRESSED = true;
  if (keycode == MOVE_UP2)
    cub3d->key_status.MOVE_UP2_PRESSED = true;
  if (keycode == MOVE_DOWN)
    cub3d->key_status.MOVE_DOWN_PRESSED = true;
  if (keycode == MOVE_DOWN2)
    cub3d->key_status.MOVE_DOWN2_PRESSED = true;
  if (keycode == MOVE_RIGHT)
    cub3d->key_status.MOVE_RIGHT_PRESSED = true;
  if (keycode == MOVE_LEFT)
    cub3d->key_status.MOVE_LEFT_PRESSED = true;
  if (keycode == ROTATE_RIGHT)
    cub3d->key_status.ROTATE_RIGHT_PRESSED = true;
  if (keycode == ROTATE_LEFT)
    cub3d->key_status.ROTATE_LEFT_PRESSED = true;
  return (0);
}

int handle_keyrelease(int keycode, void *cub3d_ptr) {
  t_cub *cub3d = (t_cub *)cub3d_ptr;

  if (keycode == ESC)
    cub3d->key_status.ESC_PRESSED = false;
  if (keycode == MOVE_UP)
    cub3d->key_status.MOVE_UP_PRESSED = false;
  if (keycode == MOVE_UP2)
    cub3d->key_status.MOVE_UP2_PRESSED = false;
  if (keycode == MOVE_DOWN)
    cub3d->key_status.MOVE_DOWN_PRESSED = false;
  if (keycode == MOVE_DOWN2)
    cub3d->key_status.MOVE_DOWN2_PRESSED = false;
  if (keycode == MOVE_RIGHT)
    cub3d->key_status.MOVE_RIGHT_PRESSED = false;
  if (keycode == MOVE_LEFT)
    cub3d->key_status.MOVE_LEFT_PRESSED = false;
  if (keycode == ROTATE_RIGHT)
    cub3d->key_status.ROTATE_RIGHT_PRESSED = false;
  if (keycode == ROTATE_LEFT)
    cub3d->key_status.ROTATE_LEFT_PRESSED = false;
  return (0);
}
