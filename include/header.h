#ifndef _CUB3D
#define _CUB3D

#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define SKY_COLOR 0x87CEEB
#define GROUND_COLOR 0x228B22
#define WALL_COLOR_X 0xFF0000
#define WALL_COLOR_Y 0x880000

#define WIDTH 1600
#define HEIGHT 900

typedef struct s_vector {
  float x;
  float y;
} t_vector;

typedef struct {
  t_vector pos;
  t_vector dir;
  t_vector plane;
} t_player;

typedef struct {
  void *img;
  char *addr;
  int bpp;
  int line_len;
  int endian;
} t_img_data;

typedef struct {
  void *mlx;
  void *win;
  t_img_data img_data;
  int **gamemap;
  t_player *player;
} t_cub;

t_vector vec_add(t_vector a, t_vector b);
t_vector vec_sub(t_vector a, t_vector b);
t_vector vec_scale(t_vector v, float scalar);
float vec_dot(t_vector a, t_vector b);
float vec_length(t_vector v);
t_vector vec_normalize(t_vector v);
t_vector vec_rotate(t_vector v, float angle);
void init_cub(t_cub *cub);
void init_player(t_player *player);
void put_pixel(t_img_data *img_data, int x, int y, int color);
void render_background(t_cub *cub);
void render_walls(t_cub *cub3d);
int handle_no_event(void *cub3d_ptr);

#endif
