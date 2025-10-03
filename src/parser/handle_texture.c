#include "../../include/header.h"

void handle_texture(t_cub *cub, char *tex_path, int argc, char **tex) {
  if (argc != 2) {
    print_error_and_exit(cub, "Texture error: many arguments");
  }
  if (*tex)
    print_error_and_exit(cub, "Duplicated texture");
  else
    *tex = ft_strdup(tex_path);
}
