#ifndef _CUB3D
#define _CUB3D

#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SKY_COLOR 0x87CEEB
#define GROUND_COLOR 0x228B22
#define WALL_COLOR_X 0xFF0000
#define WALL_COLOR_Y 0x880000

#define WIDTH 1600
#define HEIGHT 900

#define DESTROY_NOTIFY 17
#define IGNORE_MASK 0
#define KEYPRESS 2
#define KEYPRESS_MASK 1L << 0
#define ESC 65307
#define MOVE_UP 119
#define MOVE_UP2 65362
#define MOVE_DOWN 115
#define MOVE_DOWN2 65364
#define MOVE_RIGHT 100
#define MOVE_LEFT 97
#define ROTATE_RIGHT 65361
#define ROTATE_LEFT 65363

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

typedef struct s_vector {
  float x;
  float y;
} t_vector;

typedef struct {
  t_vector pos;
  t_vector dir;
  t_vector plane;
  float move_speed;
  float rot_speed;
} t_player;

typedef struct {
  void *img;
  char *addr;
  int bpp;
  int line_len;
  int endian;
} t_img_data;

typedef struct {
  void *img;
  char *addr;
  int width;
  int height;
  int bpp;
  int line_len;
  int endian;
} t_texture;

typedef struct {
  char **map;
  char *map_path;
  char *SO;
  char *NO;
  char *WE;
  char *EA;
  char *F[3];
  char *C[3];
} t_map;

typedef struct {
  void *mlx;
  void *win;
  t_img_data img_data;
  int **gamemap;
  t_player *player;
  t_texture textures[4];
  t_map *map;
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
int handle_keypress(int keycode, void *cub3d_ptr);
int game_exit(t_cub *cub);
int main_loop(t_cub *cub);
void load_all_textures(t_cub *cub);
bool parser_map(t_cub *cub, char *file);
void print_error_and_exit(t_cub *cub, char *msg);

#endif
