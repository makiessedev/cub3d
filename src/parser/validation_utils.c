#include "../../include/header.h"

bool validate_lines2(t_map *map, int i, int j) {
  if (i + 1 < map->height) {
    if (map->gamemap[i + 1][j] && map->gamemap[i + 1][j] != ' ' &&
        map->gamemap[i + 1][j] != '1')
      return false;
  }
  if (i - 1 > 0) {
    if (map->gamemap[i - 1] && map->gamemap[i - 1][j] &&
        map->gamemap[i - 1][j] != ' ' && map->gamemap[i - 1][j] != '1')
      return false;
  }
  if (j + 1 < map->width) {
    if (map->gamemap[i][j + 1] && map->gamemap[i][j + 1] != ' ' &&
        map->gamemap[i][j + 1] != '1')
      return false;
  }
  if (j - 1 > 0) {
    if (map->gamemap[i][j - 1] && map->gamemap[i][j - 1] != ' ' &&
        map->gamemap[i][j - 1] != '1')
      return false;
  }

  return true;
}
