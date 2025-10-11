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

#define WIDTH 640
#define HEIGHT 480

#define DESTROY_NOTIFY 17
#define IGNORE_MASK 0
#define KEYPRESS 2
#define KEYPRESS_MASK 1L << 0
#define KEYRELEASE 3
#define KEYRELEASE_MASK 1L << 1
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

#define M_EMPTY "\n\t "
#define M_SPACE ' '
#define M_TAB '\t'
#define M_SO "SO"
#define M_WE "WE"
#define M_EA "EA"
#define M_NO "NO"
#define M_FLOOR "F"
#define M_CEIL "C"

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
  char **map_raw_datas;
  char *map_path;
  char **gamemap;
  int width;
  int height;
  char *SO;
  char *NO;
  char *WE;
  char *EA;
  char *F[3];
  char *C[3];
} t_map;

typedef struct {
  bool ESC_PRESSED;
  bool MOVE_UP_PRESSED;
  bool MOVE_UP2_PRESSED;
  bool MOVE_DOWN_PRESSED;
  bool MOVE_DOWN2_PRESSED;
  bool MOVE_RIGHT_PRESSED;
  bool MOVE_LEFT_PRESSED;
  bool ROTATE_RIGHT_PRESSED;
  bool ROTATE_LEFT_PRESSED;
} t_key_status;

typedef struct {
  t_vector dir;
  t_vector map_pos;
  t_vector delta_dist;
  t_vector side_dist;
  int step_x;
  int step_y;
  int side; // 0 = X ; 1 Y
  float perp_dist;
  t_texture *texture;
  float wall_x;
} t_ray;

typedef struct {
  void *mlx;
  void *win;
  t_img_data img_data;
  t_player *player;
  t_texture textures[4];
  t_map *map;
  t_key_status key_status;
  t_ray *ray;
} t_cub;

typedef struct s_wall_line {
  int start;
  int end;
  int texX;
  float line_start_y;
  float line_end_y;
  float line_height;
} t_wall_line;

// src/vec_operations.c
t_vector vec_add(t_vector a, t_vector b);
t_vector vec_scale(t_vector v, float scalar);
float vec_length(t_vector v);
t_vector vec_normalize(t_vector v);
t_vector vec_rotate(t_vector v, float angle);

// ../src/initialization.c
void init_cub(t_cub *cub);
void init_player(t_player *player);

// ../src/rendering.c
void put_pixel(t_img_data *img_data, int x, int y, int color);
void render_background(t_cub *cub);
void render_walls(t_cub *cub3d);

// ../src/events.c
int handle_keypress(int keycode, void *cub3d_ptr);
int game_exit(t_cub *cub);
int handle_keyrelease(int keycode, void *cub3d_ptr);
void handle_input(t_cub *cub);

// ../main.c
int main_loop(t_cub *cub);

// ../src/textures.c
void load_all_textures(t_cub *cub);

// ../src/parser/map_parser.c
bool parser_map(t_cub *cub, char *file);

// ../src/print_error_and_exit.c
void print_error_and_exit(t_cub *cub, char *msg);
void free_cub(t_cub *cub);

// ../src/validate_position.c
bool is_border_wall(t_cub *cub, int mapX, int mapY);
bool newpos_isvalid(t_cub *cub, float new_posX, float new_posY);

// ../src/moviments.c
void move_up(t_cub *cub);
void move_down(t_cub *cub);
void move_right(t_cub *cub);
void move_left(t_cub *cub);

// ../src/rotation.c
void rotate_right(t_cub *cub);
void rotate_left(t_cub *cub);

// ../src/parser/utils.c
char *ft_remove_chars(const char *s, const char *set);
int open_file(char *file);
void pad_map_lines(char **map, int max_len);

// ../src/parser/handle_color.c
void handle_color(t_cub *cub, char **chuncks, int argc, char **colors_ref);

// ../src/parser/handle_texture.c
void handle_texture(t_cub *cub, char *tex_path, int argc, char **tex);

// ../src/parser/validation.c
void validate_map(t_cub *cub);

// ../src/parser/extract_elements.c
bool get_color_and_texture(t_cub *cub_data, t_map *map, char **elements,
                           int *i);
bool get_map(t_cub *cub_data, t_map *map, int map_height, int *i);

// ../src/parser/extract_map_utils.c
int count_map_height(t_cub *cub, int i);
void salt_to_first_linemap(t_map *map, int *i);

// ../src/parser/validation_utils.c
bool validate_lines2(t_map *map, int i, int j);
int is_file_empty(char *path);

// ../src/parser/check_cub_ext.c
bool check_cub_extension(const char *filename);

#endif
