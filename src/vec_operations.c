#include "../include/header.h"

t_vector vec_add(t_vector a, t_vector b) {
  t_vector result;
  result.x = a.x + b.x;
  result.y = a.y + b.y;
  return result;
}

t_vector vec_sub(t_vector a, t_vector b) {
  t_vector result;
  result.x = a.x - b.x;
  result.y = a.y - b.y;
  return result;
}

t_vector vec_scale(t_vector v, float scalar) {
  t_vector result;
  result.x = v.x * scalar;
  result.y = v.y * scalar;
  return result;
}

float vec_dot(t_vector a, t_vector b) { return a.x * b.x + a.y * b.y; }

float vec_length(t_vector v) { return sqrt(v.x * v.x + v.y * v.y); }

t_vector vec_normalize(t_vector v) {
  float len = vec_length(v);
  t_vector result;

  if (len == 0) {
    result.x = 0;
    result.y = 0;
    return result;
  }

  result.x = v.x / len;
  result.y = v.y / len;
  return result;
}

t_vector vec_rotate(t_vector v, float angle) {
  t_vector result;
  result.x = v.x * cos(angle) - v.y * sin(angle);
  result.y = v.x * sin(angle) + v.y * cos(angle);
  return result;
}
