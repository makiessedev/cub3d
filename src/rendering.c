#include "../include/header.h"

int create_rgb(int r, int g, int b) { return ((r << 16) | (g << 8) | b); }

void put_pixel(t_img_data *img_data, int x, int y, int color) {
  if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
    int offset = (y * img_data->line_len) + (x * (img_data->bpp / 8));
    *(unsigned int *)(img_data->addr + offset) = color;
  }
}

void render_background(t_cub *cub) {
  int C0 = ft_atoi(cub->map->C[0]);
  int C1 = ft_atoi(cub->map->C[1]);
  int C2 = ft_atoi(cub->map->C[2]);

  int F0 = ft_atoi(cub->map->F[0]);
  int F1 = ft_atoi(cub->map->F[1]);
  int F2 = ft_atoi(cub->map->F[2]);

  const int SKY_COLOR = create_rgb(C0, C1, C2);
  const int GROUND_COLOR = create_rgb(F0, F1, F2);

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
      if ((int)wallMapPos.y >= 0 && (int)wallMapPos.y < cub3d->map->height &&
          (int)wallMapPos.x >= 0 && (int)wallMapPos.x < cub3d->map->width) {
        // if (cub3d->gamemap[(int)wallMapPos.y][(int)wallMapPos.x] > 0) {
        // if (cub3d->map->gamemap[(int)wallMapPos.y][(int)wallMapPos.x] == '1')
        // {
        if (cub3d->map->gamemap[(int)wallMapPos.y][(int)wallMapPos.x] > '0') {
          hit = true;
        }
      } else {
        hit = true;
      }
    }

    float perpendicularDist;
    float wallX;
    t_texture *current_tex;
    if (hitSide == 0) // parede vertical
    {
      perpendicularDist = ddaLineSizeX - deltaDistX;
      wallX = cub3d->player->pos.y + perpendicularDist * rayDir.y;
      if (rayDir.x > 0) {
        current_tex = &cub3d->textures[WEST];
      } else {
        current_tex = &cub3d->textures[EAST];
      }
    } else {
      perpendicularDist = ddaLineSizeY - deltaDistY;
      wallX = cub3d->player->pos.x + perpendicularDist * rayDir.x;
      if (rayDir.y > 0) {
        current_tex = &cub3d->textures[NORTH];
      } else {
        current_tex = &cub3d->textures[SOUTH];
      }
    }

    perpendicularDist = fabs(perpendicularDist);
    if (perpendicularDist < 0.0001) {
      fprintf(stderr, "PerpendicularDist muito pequeno: %f\n",
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

    wallX -=
        floor(wallX); // Essa cena me frustrou bastante porque estava casusando
                      // um segfault no programa todo. E como saberia que o
                      // problema era essa varialvel? GDB hahaha
    int texX = (int)(wallX * (float)current_tex->width);

    for (int y_coord = lineStart; y_coord <= lineEnd; y_coord++) {
      int texY = (int)(((y_coord - lineStart) / (lineEndY - lineStartY)) *
                       current_tex->height);
      if (texY < 0)
        texY = 0;
      if (texY > current_tex->height)
        texY = current_tex->height - 1;

      int offset_tex =
          (texY * current_tex->line_len) + (texX * (current_tex->bpp / 8));
      unsigned int wallColor =
          *(unsigned int *)(current_tex->addr + offset_tex);

      put_pixel(&cub3d->img_data, (int)pixel, y_coord, wallColor);
    }
    pixel++;
  }
}
