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
  load_texture(cub, &cub->textures[NORTH], cub->map->NO, NORTH);
  load_texture(cub, &cub->textures[SOUTH], cub->map->SO, SOUTH);
  load_texture(cub, &cub->textures[EAST], cub->map->EA, EAST);
  load_texture(cub, &cub->textures[WEST], cub->map->WE, WEST);
}



