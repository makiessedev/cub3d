#include "../include/header.h"

void load_texture(t_cub *cub, t_texture *texture, char *relative_path, int index) {
  if (!cub->mlx) {
    ft_putendl_fd("Faile: minilibx not initialized", 2);
    exit(1);
  }

  texture->img = mlx_xpm_file_to_image(cub->mlx, relative_path, &texture->width, &texture->height);
  if (!texture->img) {
    ft_putendl_fd("Faile to load image", 2);
    exit(1);
  }

  texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_len, &texture->endian);
  if (!texture->addr) {
    ft_putendl_fd("Faile to load image addr", 2);
  }

  cub->textures[index] = *texture;
}

void load_all_textures(t_cub *cub) {
  load_texture(cub, &cub->textures[0], "./assets/textures/texture01.xpm", 0);
  load_texture(cub, &cub->textures[1], "./assets/textures/texture02.xpm", 1);
  load_texture(cub, &cub->textures[2], "./assets/textures/texture03.xpm", 2);
  load_texture(cub, &cub->textures[3], "./assets/textures/texture04.xpm", 3);
}



