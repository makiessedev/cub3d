#include "../../include/header.h"
#include <stddef.h>

static char *ft_remove_chars2(const char *s, const char *set, char *dest,
                              size_t set_len);

char *ft_remove_chars(const char *s, const char *set) {
  char *new_s;
  size_t s_len, set_len;

  if (!s || !set)
    return NULL;

  s_len = strlen(s);
  set_len = strlen(set);

  new_s = (char *)malloc(s_len + 1);
  if (!new_s)
    return NULL;

  new_s = ft_remove_chars2(s, set, new_s, set_len);
  return new_s;
}

static char *ft_remove_chars2(const char *s, const char *set, char *dest,
                              size_t set_len) {
  int char_is_in_set;
  int i;
  int j;

  i = 0;
  j = 0;
  while (s[i]) {
    char_is_in_set = 0;
    for (size_t k = 0; k < set_len; k++) {
      if (s[i] == set[k]) {
        char_is_in_set = 1;
        break;
      }
    }
    if (!char_is_in_set) {
      dest[j] = s[i];
      j++;
    }
    i++;
  }
  dest[j] = '\0';
  return dest;
}

int open_file(char *file) {
  int fd;

  fd = open(file, O_RDONLY);
  if (fd == -1) {
    perror("Error to open map");
    exit(0);
  }
  return fd;
}
