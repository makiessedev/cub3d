#include "../include/header.h"

static int count_line(t_map *map);
static int open_file(char *file);

bool parser_map(t_cub *cub, char *file) {
  t_map *map;
  int fd;
  int i;
  char *line;

  map = cub->map;
  map->map_path = file;

  fd = open_file(map->map_path);
  line = get_next_line(fd);
  map->map = ft_calloc(count_line(map), sizeof(char*));
  i = 0;
  while (line != NULL) {
    printf("%s", line);
    map->map[i] = ft_strdup(line);
    line = get_next_line(fd);
    i++;
  }
  return true;
}

static int count_line(t_map *map) {
  char *line;
  int count;
  int fd;

  fd = open_file(map->map_path);

  line = get_next_line(fd);
  count = 0;
  while (line != NULL) {
    count++;
    line = get_next_line(fd);
  }
  return (count);
}

static int open_file(char *file) {
  int fd;
  
  fd = open(file, O_RDONLY);
  if (fd == -1) {
    perror("Error to open map");
    exit(0);
  }
  return fd;
}
