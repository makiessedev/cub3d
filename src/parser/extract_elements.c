#include "../../include/header.h"
#include <stddef.h>

bool get_color_and_texture(t_cub *cub_data, t_map *map, char **elements,
                           int *i) {
  char *key;
  key = ft_strtrim(elements[0], M_EMPTY);
  int elements_len = ft_count_matrix(elements);
  if (!ft_strncmp(key, M_NO, ft_strlen(M_NO))) {
    handle_texture(cub_data, elements[1], elements_len, &(map->NO));
  } else if (!ft_strncmp(key, M_SO, ft_strlen(M_SO))) {
    handle_texture(cub_data, elements[1], elements_len, &(map->SO));
  } else if (!ft_strncmp(key, M_WE, ft_strlen(M_WE))) {
    handle_texture(cub_data, elements[1], elements_len, &(map->WE));
  } else if (!ft_strncmp(key, M_EA, ft_strlen(M_EA))) {
    handle_texture(cub_data, elements[1], elements_len, &(map->EA));
  } else if (!ft_strncmp(key, M_FLOOR, ft_strlen(M_FLOOR))) {
    handle_color(cub_data, elements, elements_len, map->F);
  } else if (!ft_strncmp(key, M_CEIL, ft_strlen(M_CEIL))) {
    handle_color(cub_data, elements, elements_len, map->C);
  } else {
    return false;
  }

  if (map->NO && map->SO && map->WE && map->EA && map->C[0] && map->F[0])
    (*i)++;

  return true;
}

bool get_map(t_cub *cub_data, t_map *map, int map_height, int *i) {
  char *line;
  int j = 0;
  map->width = 0;
  map->height = 0;

  map->gamemap = malloc(sizeof(char *) * (map_height + 1));
  while (cub_data->map->map_raw_datas[*i]) {
    line = ft_strdup(ft_strtrim(map->map_raw_datas[*i], M_EMPTY));
    if (line[0] == '\0' && map->height < map_height) {
      return false;
    } else if (line[0] == '\0') {
      (*i)++;
      continue;
    }
    free(line);
    line = ft_strdup(ft_strtrim(map->map_raw_datas[*i], "\n"));
    if (ft_strlen(line) > (size_t)map->width)
      map->width = ft_strlen(line);
    map->gamemap[j] = ft_strdup(line);
    (*i)++;
    j++;
    map->height++;
  }
  map->gamemap[j] = NULL;
  return true;
}
