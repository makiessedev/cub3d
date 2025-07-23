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
      {1, 0, 0, 0, 1, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
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

    /*float deltaDistX; //= fabs(1 / rayDir.x);
    float deltaDistY; //= fabs(1 / rayDir.y);

    if (rayDir.x == 0) {
      deltaDistX = 1;
      deltaDistY = 0;
    } else if (rayDir.y) {
      deltaDistX = fabs(1 / rayDir.x);
    }

    if (rayDir.y == 0) {
      deltaDistY = 1;
      deltaDistX = 0;
    } else if (rayDir.x) {
      deltaDistY = fabs(1 / rayDir.y);
    }*/

    float deltaDistX = (rayDir.x == 0) ? 1e30 : fabs(1.0 / rayDir.x);
    float deltaDistY = (rayDir.y == 0) ? 1e30 : fabs(1.0 / rayDir.y);

    t_vector mapPos = {floor(player->pos.x), floor(player->pos.y)};

    int stepY;
    int stepX;

    float distToSideX;
    float distToSideY;

    if (rayDir.x < 0) {
      distToSideX = (player->pos.x - mapPos.x) * deltaDistX;
      stepX = -1;
    } else {
      distToSideX = (mapPos.x + 1 - player->pos.x) * deltaDistX;
      stepX = 1;
    }

    if (rayDir.y < 0) {
      distToSideY = (player->pos.y - mapPos.y) * deltaDistY;
      stepY = -1;
    } else {
      distToSideY = (mapPos.y + 1 - player->pos.y) * deltaDistY;
      stepY = 1;
    }

    bool hit = false;

    float ddaLineSizeX = distToSideX;
    float ddaLineSizeY = distToSideY;

    int hitSide;
    float perpendicularDist;

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

    /*if (hitSide == 0) {
      perpendicularDist =
          fabs(wallMapPos.x - player->pos.x + ((1 - stepX) / 2.0)) / rayDir.x;
    } else {
      perpendicularDist =
          fabs(wallMapPos.y - player->pos.y + ((1 - stepY) / 2.0)) / rayDir.y;
    }

    if (isnan(perpendicularDist) || perpendicularDist <= 0) {
      printf("Erro: perpendicularDist inválido: %f\n", perpendicularDist);
      pixel++;
      continue;
    }*/

    if (hitSide == 0) {
      perpendicularDist = ddaLineSizeX - deltaDistX;
    } else {
      perpendicularDist = ddaLineSizeY - deltaDistY;
    }

    perpendicularDist = fabs(perpendicularDist);
    if (perpendicularDist < 0.0001) {
      printf("Erro: perpendicularDist muito pequeno: %f\n", perpendicularDist);
      continue;
    }

    float wallLineHeight = height / perpendicularDist;
    float lineStartY = (float)height / 2 - wallLineHeight / 2;
    float lineEndY = (float)height / 2 + wallLineHeight / 2;

    int lineStart = (int)lineStartY;
    int lineEnd = (int)lineEndY;
    if (lineStart < 0)
      lineStart = 0;
    if (lineEnd >= height)
      lineEnd = height - 1;

    x = (int)pixel; // coluna da tela

    int wallColor = (hitSide == 0) ? 0xFF0000 : 0x880000; // exemplo

    for (y = lineStart; y <= lineEnd; y++) {
      int offset = (y * line_len) + (x * (bpp / 8));
      *(unsigned int *)(addr + offset) = wallColor;
    }

    pixel++;
  }

  (void)player;

  mlx_put_image_to_window(mlx, win, img, 0, 0);
  mlx_loop(mlx);

  return (0);
}
