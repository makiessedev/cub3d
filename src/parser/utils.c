#include "../../include/header.h"

char *ft_remove_chars(const char *s, const char *set) {
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
