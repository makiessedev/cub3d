#include "../include/header.h"

int game_exit(t_cub *cub) {
  (void)cub;
  exit(0);
  return (0);
}

int main_loop(t_cub *cub) {
  render_background(cub);
  render_walls(cub);

  mlx_put_image_to_window(cub->mlx, cub->win, cub->img_data.img, 0, 0);

  return (0);
}

int handle_keypress(int keycode, void *cub3d_ptr) {
  t_cub *cub3d = (t_cub *)cub3d_ptr;
  t_player *player = cub3d->player;

  // Tecla ESC para sair
  if (keycode == ESC) {
    exit(0);
  }

  // Movimento para frente (W ou Seta para Cima)
  if (keycode == MOVE_UP || keycode == MOVE_UP2) {
    float new_posX = player->pos.x + player->dir.x * player->move_speed;
    float new_posY = player->pos.y + player->dir.y * player->move_speed;
    // Verifica colisão antes de mover
    if (cub3d->map->gamemap[(int)player->pos.y][(int)new_posX] == '0')
      player->pos.x = new_posX;
    if (cub3d->map->gamemap[(int)new_posY][(int)player->pos.x] == '0')
      player->pos.y = new_posY;
  }

  // Movimento para trás (S ou Seta para Baixo)
  if (keycode == MOVE_DOWN || keycode == MOVE_DOWN2) {
    float new_posX = player->pos.x - player->dir.x * player->move_speed;
    float new_posY = player->pos.y - player->dir.y * player->move_speed;
    // Verifica colisão antes de mover
    if (cub3d->map->gamemap[(int)player->pos.y][(int)new_posX] == '0')
      player->pos.x = new_posX;
    if (cub3d->map->gamemap[(int)new_posY][(int)player->pos.x] == '0')
      player->pos.y = new_posY;
  }

  // Mover para a direita (D)
  if (keycode == MOVE_RIGHT) {
    float new_posX = player->pos.x + player->plane.x * player->move_speed;
    float new_posY = player->pos.y + player->plane.y * player->move_speed;
    // Verifica colisão antes de mover
    if (cub3d->map->gamemap[(int)player->pos.y][(int)new_posX] == '0')
      player->pos.x = new_posX;
    if (cub3d->map->gamemap[(int)new_posY][(int)player->pos.x] == '0')
      player->pos.y = new_posY;
  }

  // Mover para a esquerda (A) - usando o vetor do plano da câmera
  if (keycode == MOVE_LEFT) {
    float new_posX = player->pos.x - player->plane.x * player->move_speed;
    float new_posY = player->pos.y - player->plane.y * player->move_speed;
    // Verifica colisão antes de mover
    if (cub3d->map->gamemap[(int)player->pos.y][(int)new_posX] == '0')
      player->pos.x = new_posX;
    if (cub3d->map->gamemap[(int)new_posY][(int)player->pos.x] == '0')
      player->pos.y = new_posY;
  }

  // Rotacionar para a direita (Seta para Direita)
  if (keycode == ROTATE_RIGHT) {
    player->dir = vec_rotate(player->dir, -player->rot_speed);
    player->plane = vec_rotate(player->plane, -player->rot_speed);
  }

  // Rotacionar para a esquerda (Seta para Esquerda)
  if (keycode == ROTATE_LEFT) {
    player->dir = vec_rotate(player->dir, player->rot_speed);
    player->plane = vec_rotate(player->plane, player->rot_speed);
  }

  main_loop(cub3d_ptr);

  return (0);
}
