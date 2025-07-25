#include "include/header.h"
#include "mlx/mlx.h"

#define DESTROY_NOTIFY 17
#define IGNORE_MASK 0
#define KEYPRESS 2
#define KEYPRESS_MASK 1L << 0
#define ESC 65307
#define MOVE_UP 119
#define MOVE_UP2 65362
#define MOVE_DOWN 115
#define MOVE_DOWN2 65364
#define MOVE_RIGHT 100
#define MOVE_LEFT 97

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

  printf("Tecla pressionada: %d\n", keycode);

  // Tecla ESC para sair
  // Keycode 65307 para ESC (Linux)
  if (keycode == 65307) {
    // cleanup(cub3d);
    exit(0);
  }

  // Movimento para frente (W ou Seta para Cima)
  // Keycode 119 para 'W' (Linux)
  // Keycode 65362 para Seta para Cima (Linux)
  if (keycode == MOVE_UP || keycode == MOVE_UP2) {
    float new_posX = player->pos.x + player->dir.x * player->move_speed;
    float new_posY = player->pos.y + player->dir.y * player->move_speed;
    // Verifica colisão antes de mover
    if (cub3d->gamemap[(int)player->pos.y][(int)new_posX] == 0)
      player->pos.x = new_posX;
    if (cub3d->gamemap[(int)new_posY][(int)player->pos.x] == 0)
      player->pos.y = new_posY;
  }

  // Movimento para trás (S ou Seta para Baixo)
  // Keycode 115 para 'S' (Linux)
  // Keycode 65364 para Seta para Baixo (Linux)
  if (keycode == MOVE_DOWN || keycode == MOVE_DOWN2) {
    float new_posX = player->pos.x - player->dir.x * player->move_speed;
    float new_posY = player->pos.y - player->dir.y * player->move_speed;
    // Verifica colisão antes de mover
    if (cub3d->gamemap[(int)player->pos.y][(int)new_posX] == 0)
      player->pos.x = new_posX;
    if (cub3d->gamemap[(int)new_posY][(int)player->pos.x] == 0)
      player->pos.y = new_posY;
  }

  // Mover para a direita (D) - usando o vetor do plano da câmera
  // Keycode 100 para 'D' (Linux)
  if (keycode == MOVE_RIGHT) {
    float new_posX = player->pos.x + player->plane.x * player->move_speed;
    float new_posY = player->pos.y + player->plane.y * player->move_speed;
    // Verifica colisão antes de mover
    if (cub3d->gamemap[(int)player->pos.y][(int)new_posX] == 0)
      player->pos.x = new_posX;
    if (cub3d->gamemap[(int)new_posY][(int)player->pos.x] == 0)
      player->pos.y = new_posY;
  }

  // Mover para a esquerda (A) - usando o vetor do plano da câmera
  // Keycode 97 para 'A' (Linux)
  if (keycode == MOVE_LEFT) {
    float new_posX = player->pos.x - player->plane.x * player->move_speed;
    float new_posY = player->pos.y - player->plane.y * player->move_speed;
    // Verifica colisão antes de mover
    if (cub3d->gamemap[(int)player->pos.y][(int)new_posX] == 0)
      player->pos.x = new_posX;
    if (cub3d->gamemap[(int)new_posY][(int)player->pos.x] == 0)
      player->pos.y = new_posY;
  }

  // Rotacionar para a direita (Seta para Direita)
  // Keycode 65363 para Seta para Direita (Linux)
  if (keycode == 65361) {
    player->dir =
        vec_rotate(player->dir, -player->rot_speed); // Rotaciona a direção
    player->plane = vec_rotate(
        player->plane, -player->rot_speed); // Rotaciona o plano da câmera
  }

  // Rotacionar para a esquerda (Seta para Esquerda)
  // Keycode 123 para Seta para Esquerda (macOS)
  // Keycode 65361 para Seta para Esquerda (Linux)
  if (keycode == 65363) {
    player->dir =
        vec_rotate(player->dir, player->rot_speed); // Rotaciona a direção
    player->plane = vec_rotate(
        player->plane, player->rot_speed); // Rotaciona o plano da câmera
  }

  main_loop(cub3d_ptr);

  return (0);
}

int main(void) {
  t_cub cub3d;

  init_cub(&cub3d);

  cub3d.player->dir = vec_rotate(cub3d.player->dir, 1.0);
  cub3d.player->plane = vec_rotate(cub3d.player->plane, 1.0);

  mlx_loop_hook(cub3d.mlx, &main_loop, &cub3d);
  mlx_hook(cub3d.win, KEYPRESS, KEYPRESS_MASK, &handle_keypress, &cub3d);
  mlx_hook(cub3d.win, DESTROY_NOTIFY, IGNORE_MASK, &game_exit, &cub3d);

  mlx_loop(cub3d.mlx);

  return (0);
}
