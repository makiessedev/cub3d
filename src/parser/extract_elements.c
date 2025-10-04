#include "../../include/header.h"

static int count_map_height(t_cub *cub, int i);

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

bool get_map(t_cub *cub_data, t_map *map, int *i) {
  int map_height = count_map_height(cub_data, *i);
  map->gamemap = malloc(sizeof(char *) * (map_height + 1));
  char *line;
  int j = 0;
  int width = 0;
  int height = 0;

  char *raw_line = ft_strdup(ft_strtrim(map->map_raw_datas[*i], M_EMPTY));
  while (raw_line[0] == '\0') {
    free(raw_line);
    (*i)++;
    raw_line = ft_strdup(ft_strtrim(map->map_raw_datas[*i], M_EMPTY));
  }
  free(raw_line);
  while (cub_data->map->map_raw_datas[*i]) {
    raw_line = ft_strdup(ft_strtrim(map->map_raw_datas[*i], M_EMPTY));
    if (raw_line[0] == '\0' && height < map_height) {
      return false;
    } else if (raw_line[0] == '\0') {
      (*i)++;
      continue;
    }
    line = ft_strdup(ft_strtrim(map->map_raw_datas[*i], "\n"));
    int current_width = ft_strlen(line);
    if (current_width > width)
      width = current_width;

    map->gamemap[j] = ft_strdup(line);
    (*i)++;
    j++;
    height++;
  }
  map->width = width;
  map->height = height;
  map->gamemap[j] = NULL;
  return true;
}

static int count_map_height(t_cub *cub, int i) {
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
