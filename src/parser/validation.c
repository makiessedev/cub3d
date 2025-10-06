#include "../../include/header.h"

static bool validate_first_and_last_line(t_map *map);
static bool validate_lines(t_map *map);
static void validate_and_get_player_position(t_cub *cub);

void validate_map(t_cub *cub) {
  if (validate_first_and_last_line(cub->map) == false)
    print_error_and_exit(cub, "Error\nInvalid map");
  if (validate_lines(cub->map) == false)
    print_error_and_exit(cub, "Error\nInvalid map");
  validate_and_get_player_position(cub);
}

static bool validate_first_and_last_line(t_map *map) {
  char *first_line = map->gamemap[0];
  char *last_line = map->gamemap[map->height - 1];

  int i = 0;
  while (first_line[i] != '\0') {
    if (first_line[i] != ' ' && first_line[i] != '1')
      return false;
    i++;
  }

  i = 0;
  while (last_line[i] != '\0') {
    if (last_line[i] != ' ' && last_line[i] != '1')
      return false;
    i++;
  }

  return true;
}

static bool validate_lines(t_map *map) {
  int i = 0;
  int j = 0;

  while (map->gamemap[i] != NULL) {
    char *line = ft_strdup(ft_strtrim(map->gamemap[i], M_EMPTY));
    if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
      return false;
    j = 0;
    while (map->gamemap[i][j] != '\0') {
      if (map->gamemap[i][j] != ' ' && map->gamemap[i][j] != '0' &&
          map->gamemap[i][j] != '1' && map->gamemap[i][j] != 'N' &&
          map->gamemap[i][j] != 'S' && map->gamemap[i][j] != 'E' &&
          map->gamemap[i][j] != 'W') {
        return false;
      }
      if (map->gamemap[i][j] == ' ') {
        if (validate_lines2(map, i, j) == false)
          return false;
      }
      j++;
    }
    i++;
  }

  return true;
}

static void validate_and_get_player_position(t_cub *cub) {
  int y = 0;
  int x = 0;
  char **lines = cub->map->gamemap;
  char *line;

  while (lines[y] != NULL) {
    line = ft_strdup(lines[y]);
    x = 0;
    while (line[x] != '\0') {
      if (line[x] == 'N' || line[x] == 'S' || line[x] == 'E' ||
          line[x] == 'W') {
        if (cub->player->pos.x)
          print_error_and_exit(cub, "Error\nDuplated player");
        cub->player->pos.x = x + 0.5;
        cub->player->pos.y = y + 0.5;
        cub->map->gamemap[y][x] = '0';
      }
      x++;
    }
    y++;
  }
}
