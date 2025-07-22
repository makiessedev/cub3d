#ifndef _CUB3D
#define _CUB3D

#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct s_vector {
  float x;
  float y;
} t_vector;

typedef struct {
  t_vector pos;
  t_vector dir;
  t_vector plane;
} t_player;

t_vector vec_add(t_vector a, t_vector b);
t_vector vec_sub(t_vector a, t_vector b);
t_vector vec_scale(t_vector v, float scalar);
float vec_dot(t_vector a, t_vector b);
float vec_length(t_vector v);
t_vector vec_normalize(t_vector v);
t_vector vec_rotate(t_vector v, float angle);

#endif
