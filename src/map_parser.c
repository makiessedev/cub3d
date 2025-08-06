#include "../include/header.h"

static int count_line(t_map *map);
static int open_file(char *file);
static void save_textures_and_color(t_cub *cub);
static char *ft_remove_chars(const char *s, const char *set);

static void handle_texture(t_cub *cub, char *tex_path, int argc, char **tex);
static void handle_color(t_cub *cub, char **chuncks, int argc, char **colors_ref);
static void set_colors(t_cub *cub, char *colors_raw, char **colors_ref);
static char **split_line(t_cub *cub, char *map_line, int *i);

static int count_map_height(t_cub *cub, int i);
static void print_elements(t_map *map);

bool parser_map(t_cub *cub, char *file) {
  t_map *map;
  int fd;
  int i;
  char *line;

  map = cub->map;
  map->map_path = file;

  fd = open_file(map->map_path);
  line = get_next_line(fd);
  map->map_raw_datas = ft_calloc(count_line(map)+1, sizeof(char*));
  i = 0;
  while (line != NULL) {
    map->map_raw_datas[i] = ft_strdup(line);
    line = get_next_line(fd);
    i++;
  }
  map->map_raw_datas[i] = NULL;
  save_textures_and_color(cub);
  print_elements(map);
  return true;
}

static void save_textures_and_color(t_cub *cub) {
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
    }
    else if (!ft_strncmp(key, M_FLOOR, ft_strlen(M_FLOOR))) {
      handle_color(cub, chuncks, chunck_len, map->F);
    }
    else if (!ft_strncmp(key, M_CEIL, ft_strlen(M_CEIL))) {
      handle_color(cub, chuncks, chunck_len, map->C);
    } else {
      print_error_and_exit(cub, "Invalid Key: Color or Textures");
    }

    if (map->NO && map->SO && map->WE && map->EA && map->C[0] && map->F[0]) {
      i++;
      map->gamemap = malloc(sizeof(char*) * (count_map_height(cub, i)+10));
      char *line;
      int j = 0;
      while (cub->map->map_raw_datas[i]) {
        line = ft_strdup(ft_strtrim(map->map_raw_datas[i], M_EMPTY));
        printf("%s\n", line);
        if (line[0] == '\0') {
          i++;
          continue;
        }
        map->gamemap[j] = ft_strdup(line);
        i++;
        j++;
      }
      return;
    }
    i++;
  }
}

static void print_elements(t_map *map) {
  printf("NO - %s\n", map->NO);
  printf("SO - %s\n", map->SO);
  printf("WE - %s\n", map->WE);
  printf("EA - %s\n", map->EA);

  for (int i = 0; i < 3; i++) {
    printf("F %s\n", map->F[i]);
  }

  for (int i = 0; i < 3; i++) {
    printf("C %s\n", map->C[i]);
  }

  for (int i = 0; map->gamemap[i]; i++) {
    printf("%s\n", map->gamemap[i]);
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

static void handle_color(t_cub *cub, char **chuncks, int argc, char **colors_ref) {
  const char *EMPTY = "\t ";

  if (argc >= 2 && argc <= 6) {
    char *color;
    color = ft_strdup(chuncks[1]);
    if (argc > 2) {
      char *temp;
      int i = 2;
      while (chuncks[i]) {
        temp = ft_strdup(color);
        free(color);
        color = ft_strjoin(temp, chuncks[i]);
        free(temp);
        i++;
      }
      temp = strdup(color);
      free(color);
      color = ft_remove_chars(temp, EMPTY);
      free(temp);
    }
    set_colors(cub, color, colors_ref);
  } else {
    printf("arg-> %i", argc);
    print_error_and_exit(cub, "Invalid arguments of colors");
  }
}

static void set_colors(t_cub *cub, char *colors_raw, char **colors_ref) {
  char **colors = ft_split(colors_raw, ',');
  if (ft_count_matrix(colors) > 3)
    print_error_and_exit(cub, "Invalid color many arguments");
  for (int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if (ft_isprint(colors[i][j])) {
        if (!ft_isdigit(colors[i][j])) {
          print_error_and_exit(cub, "Invalid digit color");
        }
      }
    }
    int digit = ft_atoi(colors[i]);
    if (digit > 255 || digit < 0)
      print_error_and_exit(cub, "Invalid Color");
    if (colors_ref[i])
      print_error_and_exit(cub, "Invalid color: duplicated value");
    colors_ref[i] = ft_strdup(colors[i]);
  }
}

static void handle_texture(t_cub *cub, char *tex_path, int argc, char **tex) {
  if (argc != 2) {
    print_error_and_exit(cub, "Texture error: many arguments");
  }
  if (*tex)
    print_error_and_exit(cub, "Duplicated texture");
  else
    *tex = ft_strdup(tex_path);
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

static char *ft_remove_chars(const char *s, const char *set) {
    char *new_s;
    int i, j;
    size_t s_len, set_len;

    if (!s || !set)
        return NULL;
    
    s_len = strlen(s);
    set_len = strlen(set);

    new_s = (char *)malloc(s_len + 1);
    if (!new_s)
        return NULL;

    i = 0;
    j = 0;
    while (s[i]) {
        int char_is_in_set = 0;
        for (size_t k = 0; k < set_len; k++) {
            if (s[i] == set[k]) {
                char_is_in_set = 1;
                break;
            }
        }
        if (!char_is_in_set) {
            new_s[j] = s[i];
            j++;
        }
        i++;
    }
    new_s[j] = '\0';
    return new_s;
}
