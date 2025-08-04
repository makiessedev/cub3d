#include "libft.h"

void ft_free_matrix(char **mat) {
  int i;

  if (mat == NULL) {
      return;
  }

  i = 0;
  while (mat[i] != NULL) {
      free(mat[i]);
      i++;
  }
  free(mat);
}
