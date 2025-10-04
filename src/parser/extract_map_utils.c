#include "../../include/header.h"

int count_map_height(t_cub *cub, int i) {
  int map_hight = 0;
  char *line;
  while (cub->map->map_raw_datas[i]) {
    line = ft_strdup(ft_strtrim(cub->map->map_raw_datas[i], M_EMPTY));
    if (line[0] == '\0') {
      i++;
      continue;
    }
    if (line[0] != '1') {
      print_error_and_exit(cub, "Invalid Map");
    }
    map_hight++;
    i++;
  }
  return map_hight;
}

void salt_to_first_linemap(t_map *map, int *i) {
  char *line = ft_strdup(ft_strtrim(map->map_raw_datas[*i], M_EMPTY));
  while (line[0] == '\0') {
    free(line);
    (*i)++;
    line = ft_strdup(ft_strtrim(map->map_raw_datas[*i], M_EMPTY));
  }
  free(line);
}
