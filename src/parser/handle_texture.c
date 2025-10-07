#include "../../include/header.h"

static void load_texture(t_cub *cub, t_texture *texture, char *relative_path,
                         int index);

void handle_texture(t_cub *cub, char *tex_path, int argc, char **tex) {
  if (argc != 2) {
    print_error_and_exit(cub, "Texture error: many arguments");
  }
  if (*tex)
    print_error_and_exit(cub, "Duplicated texture");
  else
    *tex = ft_strdup(tex_path);
}

void load_all_textures(t_cub *cub) {
  load_texture(cub, &cub->textures[NORTH], cub->map->NO, NORTH);
  load_texture(cub, &cub->textures[SOUTH], cub->map->SO, SOUTH);
  load_texture(cub, &cub->textures[EAST], cub->map->EA, EAST);
  load_texture(cub, &cub->textures[WEST], cub->map->WE, WEST);
}

static void load_texture(t_cub *cub, t_texture *texture, char *relative_path,
                         int index) {
  if (!cub->mlx)
    print_error_and_exit(cub, "Faile: minilibx not initialized");

  texture->img = mlx_xpm_file_to_image(cub->mlx, relative_path, &texture->width,
                                       &texture->height);
  if (!texture->img)
    print_error_and_exit(cub, "Faile to load image");

  texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
                                    &texture->line_len, &texture->endian);
  if (!texture->addr)
    print_error_and_exit(cub, "Faile to load image addr");

  cub->textures[index] = *texture;
}
