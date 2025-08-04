#include "../include/header.h"

bool parser_map(t_cub *cub, char *file) {
  (void)cub;
  (void)file;

  int fd = open(file, O_RDONLY);
  if (fd == -1) {
    perror("Error to open map");
    exit(0);
  }
  char *line = get_next_line(fd);
  while (line) {
    printf("%s", line);
    line = get_next_line(fd);
  }
  return true;
}
