#include "../include/header.h"

void print_error_and_exit(t_cub *cub, char *msg) {
  (void)cub;
  ft_putendl_fd(msg, 2);
  exit(0);
}
