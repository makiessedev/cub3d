#include "../include/header.h"

static int count_line(t_map *map);
static int open_file(char *file);
static void save_textures_and_color(t_cub *cub);
static char *ft_remove_chars(const char *s, const char *set);

bool parser_map(t_cub *cub, char *file) {
  t_map *map;
  int fd;
  int i;
  char *line;

  map = cub->map;
  map->map_path = file;

  fd = open_file(map->map_path);
  line = get_next_line(fd);
  map->map = ft_calloc(count_line(map)+1, sizeof(char*));
  i = 0;
  while (line != NULL) {
    map->map[i] = ft_strdup(line);
    line = get_next_line(fd);
    i++;
  }
  map->map[i] = NULL;
  save_textures_and_color(cub);
  return true;
}

static void save_textures_and_color(t_cub *cub) {
  const char *EMPTY = "\t ";
  const char SPACE = ' ';
  const char TAB = '\t';
  const char *SO = "SO";
  const char *WE = "WE";
  const char *EA = "EA";
  const char *NO = "NO";
  const char *F = "F";
  const char *C = "C";
  char *key;

  int i = 0;
  char *line;
  char **chuncks;
  t_map *map = cub->map;

  while (map->map[i]) {
    line = ft_strtrim(map->map[i], EMPTY);
    if (ft_strlen(line) == 0 || ft_strlen(line) == 1) {
      i++;
      continue;
    }
    chuncks = ft_split(line, SPACE);
    if (ft_count_matrix(chuncks) == 1) {
      ft_free_matrix(chuncks);
      chuncks = ft_split(line, TAB);
      if (ft_count_matrix(chuncks) == 1) {
        print_error_and_exit(cub, "invalid color or textures");
      }
    }

    key = ft_strtrim(chuncks[0], EMPTY);
    int chunck_len = ft_count_matrix(chuncks);
    if (!ft_strncmp(key, NO, ft_strlen(NO))) {
      if (chunck_len != 2) {
        print_error_and_exit(cub, "Texture error: many arguments");
      }
      if (map->NO)
        print_error_and_exit(cub, "Duplicated texture");
      else
        map->NO = ft_strdup(chuncks[1]);
    } else if (!ft_strncmp(key, SO, ft_strlen(SO))) {
      if (chunck_len != 2) {
        print_error_and_exit(cub, "Texture error: many arguments");
      }
      if (map->SO)
        print_error_and_exit(cub, "Duplicated texture");
      else
        map->SO = ft_strdup(chuncks[1]);
    } else if (!ft_strncmp(key, WE, ft_strlen(WE))) {
      if (chunck_len != 2) {
        print_error_and_exit(cub, "Texture error: many arguments");
      }
      if (map->WE)
        print_error_and_exit(cub, "Duplicated texture");
      else
        map->WE = ft_strdup(chuncks[1]);
    } else if (!ft_strncmp(key, EA, ft_strlen(EA))) {
      if (chunck_len != 2) {
        print_error_and_exit(cub, "Texture error: many arguments");
      }
      if (map->EA)
        print_error_and_exit(cub, "Duplicated texture");
      else
        map->EA = ft_strdup(chuncks[1]);
    } 


    else if (!ft_strncmp(key, F, ft_strlen(F))) {
      if (chunck_len >= 2 && chunck_len <= 6) {
        char *color;
        color = ft_strdup(chuncks[1]);
        if (chunck_len > 2) {
          free(color);
          color = ft_strdup(chuncks[1]);
          char *temp;
          if (chuncks[2]) {
            temp = ft_strdup(color);
            free(color);
            color = ft_strjoin(temp, chuncks[2]);
          }
          if (chuncks[3]) {
            temp = ft_strdup(color);
            free(color);
            color = ft_strjoin(temp, chuncks[3]);
            free(temp);
          }
          if (chuncks[4]) {
            temp = ft_strdup(color);
            free(color);
            color = ft_strjoin(temp, chuncks[4]);
            free(temp);
          }
          if (chuncks[5]) {
            temp = ft_strdup(color);
            free(color);
            color = ft_strjoin(temp, chuncks[5]);
          }
          temp = strdup(color);
          free(color);
          color = ft_remove_chars(temp, EMPTY);
          free(temp);
        }
        char **colors = ft_split(color, ',');
        if (ft_count_matrix(colors) > 3)
          print_error_and_exit(cub, "Invalid color many arguments");
        for (int i = 0; i < 3; i++) {
          for(int j = 0; j < 3; j++) {
              printf("%c ", (char)colors[i][j]);
            if (!ft_isdigit(colors[i][j])) {
              printf("-> %c", colors[i][j]);
              print_error_and_exit(cub, "Invalid digit color");
            }
          }
          int digit = ft_atoi(colors[i]);
          if (digit > 255 || digit < 0)
              print_error_and_exit(cub, "Invalid Color");
          if (map->F[i])
              print_error_and_exit(cub, "Invalid color: duplicated value");
          map->F[i] = ft_strdup(colors[i]);
        }
      } else 
        print_error_and_exit(cub, "Invalid arguments of colors");
      printf("%s", map->F[0]);
      printf("%s", map->F[1]);
      printf("%s", map->F[2]);
    }
    else if (!ft_strncmp(key, C, ft_strlen(C))) {
      printf("%s\n", key);
    } else {
      printf("%s", key);
      print_error_and_exit(cub, "Invalid Key: Color or Textures");
    }
    i++;
  }
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
