#include "../include/header.h"

void put_pixel(t_img_data *img_data, int x, int y, int color) {
  if (x >= 0 && x < 1600 && y >= 0 && y < 900) { // Adicione checks de limite
    int offset = (y * img_data->line_len) + (x * (img_data->bpp / 8));
    *(unsigned int *)(img_data->addr + offset) = color;
  }
}

void render_background(t_cub *cub) {
  int y = 0;
  while (y < HEIGHT) {
    int color;
    if (y < HEIGHT / 2)
      color = SKY_COLOR;
    else
      color = GROUND_COLOR;
    int x = 0;
    while (x < WIDTH) {
      put_pixel(&cub->img_data, x, y, color);
      x++;
    }
    y++;
  }
}

void render_walls(t_cub *cub3d) {
  float pixel = 0;
  while (pixel < WIDTH) {
    float multiplier = 2 * (pixel / WIDTH) - 1;
    t_vector cameraPixel = vec_scale(cub3d->player->plane, multiplier);
    t_vector rayDir = vec_add(cub3d->player->dir, cameraPixel);

    float deltaDistX = (rayDir.x == 0) ? 1e30 : fabs(1.0 / rayDir.x);
    float deltaDistY = (rayDir.y == 0) ? 1e30 : fabs(1.0 / rayDir.y);

    t_vector mapPos = {floor(cub3d->player->pos.x),
                       floor(cub3d->player->pos.y)};

    int stepY;
    int stepX;

    float distToSideX;
    float distToSideY;

    if (rayDir.x < 0) {
      distToSideX = (cub3d->player->pos.x - mapPos.x) * deltaDistX;
      stepX = -1;
    } else {
      distToSideX = (mapPos.x + 1 - cub3d->player->pos.x) * deltaDistX;
      stepX = 1;
    }

    if (rayDir.y < 0) {
      distToSideY = (cub3d->player->pos.y - mapPos.y) * deltaDistY;
      stepY = -1;
    } else {
      distToSideY = (mapPos.y + 1 - cub3d->player->pos.y) * deltaDistY;
      stepY = 1;
    }

    bool hit = false;
    float ddaLineSizeX = distToSideX;
    float ddaLineSizeY = distToSideY;
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
      if ((int)wallMapPos.y >= 0 && (int)wallMapPos.y < 10 &&
          (int)wallMapPos.x >= 0 && (int)wallMapPos.x < 10) {
        if (cub3d->gamemap[(int)wallMapPos.y][(int)wallMapPos.x] > 0) {
          hit = true;
        }
      } else {
        hit = true;
      }
    }

    float perpendicularDist;
    if (hitSide == 0) {
      perpendicularDist = ddaLineSizeX - deltaDistX;
    } else {
      perpendicularDist = ddaLineSizeY - deltaDistY;
    }

    perpendicularDist = fabs(perpendicularDist);
    if (perpendicularDist < 0.0001) {
      fprintf(stderr, "Erro: perpendicularDist muito pequeno: %f\n",
              perpendicularDist);
      pixel++;
      continue;
    }

    float wallLineHeight = HEIGHT / perpendicularDist;
    float lineStartY = (float)HEIGHT / 2 - wallLineHeight / 2;
    float lineEndY = (float)HEIGHT / 2 + wallLineHeight / 2;

    int lineStart = (int)lineStartY;
    int lineEnd = (int)lineEndY;
    if (lineStart < 0)
      lineStart = 0;
    if (lineEnd >= HEIGHT)
      lineEnd = HEIGHT - 1;

    int wallColor = (hitSide == 0) ? WALL_COLOR_X : WALL_COLOR_Y;

    for (int y_coord = lineStart; y_coord <= lineEnd; y_coord++) {
      put_pixel(&cub3d->img_data, (int)pixel, y_coord, wallColor);
    }
    pixel++;
  }
}
