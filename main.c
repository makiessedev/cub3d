#include "include/header.h"

int main(void) {
  void *mlx;
  void *win;
  void *img;
  char *addr;
  int width;
  int height;
  int bpp;
  int line_len;
  int endian;
  int sky_color = 0x87CEEB;
  int ground_color = 0x228B22;
  int color;
  int y;
  int x;

  width = 1600;
  height = 900;
  y = 0;
  x = 0;

  mlx = mlx_init();
  win = mlx_new_window(mlx, width, height, "Cub3D");

  img = mlx_new_image(mlx, width, height);
  addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);

  int gamemap[10][10] = {
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  };

  t_player *player = malloc(sizeof(t_player));

  player->pos.x = 5;
  player->pos.y = 5;

  player->dir.x = 0;
  player->dir.y = -1;

  player->plane.x = 0.66;
  player->plane.y = 0;

  while (y < height) {
    if (y < height / 2)
      color = sky_color;
    else
      color = ground_color;
    x = 0;
    while (x < width) {
      int offset = (y * line_len) + (x * (bpp / 8));
      *(unsigned int *)(addr + offset) = color;
      x++;
    }
    y++;
  }

  float pixel = 0;
  while (pixel < width) {
    float multiplier = 2 * (pixel / width) - 1;
    t_vector cameraPixel = vec_scale(player->plane, multiplier);
    t_vector rayDir = vec_add(player->dir, cameraPixel);

    float deltaDistX = fabs(vec_length(rayDir) / rayDir.x);
    float deltaDistY = fabs(vec_length(rayDir) / rayDir.y);

    t_vector mapPos = {floor(player->pos.x), floor(player->pos.y)};

    int stepY;
    int stepX;

    int distToSideX;
    int distToSideY;

    if (rayDir.x < 0) {
      distToSideX = (player->pos.x - mapPos.x) * deltaDistX;
      stepX = -1;
    } else {
      distToSideX = (mapPos.x + 1 - player->pos.x) * deltaDistX;
      stepX = -1;
    }

    if (rayDir.y < 0) {
      distToSideY = (player->pos.y - mapPos.y) * deltaDistY;
      stepY = -1;
    } else {
      distToSideY = (mapPos.y + 1 - player->pos.y) * deltaDistY;
      stepY = 1;
    }

    bool hit = false;

    int ddaLineSizeX = distToSideX;
    int ddaLineSizeY = distToSideY;

    int hitSide;

    t_vector wallMapPos = {mapPos.x, mapPos.y};

    while (hit == false) {
      if (ddaLineSizeX < ddaLineSizeY) {
        wallMapPos.x += stepX;
        ddaLineSizeX += deltaDistX;
        hitSide = 0;
      } else {
        wallMapPos.y += stepY;
        ddaLineSizeY += deltaDistY;
        hitSide = 1;
      }
      if (gamemap[(int)wallMapPos.y][(int)wallMapPos.x] > 0) {
        hit = true;
      }
    }

    pixel++;
  }

  (void)player;

  mlx_put_image_to_window(mlx, win, img, 0, 0);
  mlx_loop(mlx);

  return (0);
}
