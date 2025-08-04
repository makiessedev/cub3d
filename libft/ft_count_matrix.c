#include "libft.h"

int ft_count_matrix(char **mat) {
  int count = 0;

  while (mat[count])
    count++;
  return count;
}
