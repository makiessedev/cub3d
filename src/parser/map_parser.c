#include "../../include/header.h"

static int count_line(t_map *map);
static int open_file(char *file);
static void save_elements(t_cub *cub);
static char **split_line(t_cub *cub, char *map_line, int *i);
static int count_map_height(t_cub *cub, int i);

bool parser_map(t_cub *cub, char *file) {
  t_map *map;
  int fd;
  int i;
  char *line;

  map = cub->map;
  map->map_path = file;

  fd = open_file(map->map_path);
  line = get_next_line(fd);
  map->map_raw_datas = ft_calloc(count_line(map) + 1, sizeof(char *));
  i = 0;
  while (line != NULL) {
    map->map_raw_datas[i] = ft_strdup(line);
    line = get_next_line(fd);
    i++;
  }
  map->map_raw_datas[i] = NULL;

  save_elements(cub);
  validate_map(cub);

  return true;
}

static void save_elements(t_cub *cub) {
  char *key;
  int i = 0;
  char **chuncks;
  t_map *map = cub->map;

  while (map->map_raw_datas[i]) {
    chuncks = split_line(cub, map->map_raw_datas[i], &i);
    if (chuncks == NULL)
      continue;

    key = ft_strtrim(chuncks[0], M_EMPTY);
    int chunck_len = ft_count_matrix(chuncks);
    if (!ft_strncmp(key, M_NO, ft_strlen(M_NO))) {
      handle_texture(cub, chuncks[1], chunck_len, &(map->NO));
    } else if (!ft_strncmp(key, M_SO, ft_strlen(M_SO))) {
      handle_texture(cub, chuncks[1], chunck_len, &(map->SO));
    } else if (!ft_strncmp(key, M_WE, ft_strlen(M_WE))) {
      handle_texture(cub, chuncks[1], chunck_len, &(map->WE));
    } else if (!ft_strncmp(key, M_EA, ft_strlen(M_EA))) {
      handle_texture(cub, chuncks[1], chunck_len, &(map->EA));
    } else if (!ft_strncmp(key, M_FLOOR, ft_strlen(M_FLOOR))) {
      handle_color(cub, chuncks, chunck_len, map->F);
    } else if (!ft_strncmp(key, M_CEIL, ft_strlen(M_CEIL))) {
      handle_color(cub, chuncks, chunck_len, map->C);
    } else {
      print_error_and_exit(cub, "Invalid Key: Color or Textures");
    }

    if (map->NO && map->SO && map->WE && map->EA && map->C[0] && map->F[0]) {
      i++;
      int map_height = count_map_height(cub, i);
      map->gamemap = malloc(sizeof(char *) * (map_height + 1));
      char *line;
      int j = 0;
      int width = 0;
      int height = 0;

      char *temp = ft_strdup(ft_strtrim(map->map_raw_datas[i], M_EMPTY));
      while (temp[0] == '\0') {
        free(temp);
        i++;
        temp = ft_strdup(ft_strtrim(map->map_raw_datas[i], M_EMPTY));
      }
      free(temp);
      while (cub->map->map_raw_datas[i]) {
        temp = ft_strdup(ft_strtrim(map->map_raw_datas[i], M_EMPTY));
        if (temp[0] == '\0' && height < map_height) {
          print_error_and_exit(cub, "Error\nSpace inside map");
        } else if (temp[0] == '\0') {
          i++;
          continue;
        }
        line = ft_strdup(ft_strtrim(map->map_raw_datas[i], "\n"));
        int current_width = ft_strlen(line);
        if (current_width > width)
          width = current_width;

        map->gamemap[j] = ft_strdup(line);
        i++;
        j++;
        height++;
      }
      map->width = width;
      map->height = height;
      map->gamemap[j] = NULL;
      return;
    }
    i++;
  }
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

static char **split_line(t_cub *cub, char *map_line, int *i) {
  char **chuncks;
  char *line = ft_strtrim(map_line, M_EMPTY);

  if (ft_strlen(line) == 0 || ft_strlen(line) == 1) {
    (*i)++;
    return NULL;
  }
  chuncks = ft_split(line, M_SPACE);
  if (ft_count_matrix(chuncks) == 1) {
    ft_free_matrix(chuncks);
    chuncks = ft_split(line, M_TAB);
    if (ft_count_matrix(chuncks) == 1) {
      print_error_and_exit(cub, "invalid color or textures");
    }
  }
  return chuncks;
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
