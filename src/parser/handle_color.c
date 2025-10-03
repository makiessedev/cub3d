#include "../../include/header.h"

static void set_colors(t_cub *cub, char *colors_raw, char **colors_ref);

void handle_color(t_cub *cub, char **chuncks, int argc, char **colors_ref) {
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
    for (int j = 0; j < 3; j++) {
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
