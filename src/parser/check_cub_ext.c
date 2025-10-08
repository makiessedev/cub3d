#include "../../include/header.h"

int check_cub_extension(const char *filename) {
  int len;

  if (!filename)
    return (0);

  len = ft_strlen(filename);
  if (len < 5)
    return (0);

  if (filename[len - 4] == '.' && filename[len - 3] == 'c' &&
      filename[len - 2] == 'u' && filename[len - 1] == 'b')
    return (1);

  return (0);
}
