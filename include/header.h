/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 05:19:03 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 23:11:09 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H
#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 1200
#define HEIGHT 780

#define DESTROY_NOTIFY 17
#define IGNORE_MASK 0
#define KEYPRESS 2
#define KEYRELEASE 3
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

typedef struct s_player {
  t_vector pos;
  t_vector dir;
  t_vector plane;
  float move_speed;
  float rot_speed;
  char orientation;
} t_player;

typedef struct s_img_data {
  void *img;
  char *addr;
  int bpp;
  int line_len;
  int endian;
} t_img_data;

typedef struct s_texture {
  void *img;
  char *addr;
  int width;
  int height;
  int bpp;
  int line_len;
  int endian;
} t_texture;

typedef struct s_map {
  char **map_raw_datas;
  char *map_path;
  char **gamemap;
  int width;
  int height;
  char *so;
  char *no;
  char *we;
  char *ea;
  char *f[3];
  char *c[3];
} t_map;

typedef struct s_key_status {
  bool esc_pressed;
  bool move_up_pressed;
  bool move_up2_pressed;
  bool move_down_pressed;
  bool move_down2_pressed;
  bool move_right_pressed;
  bool move_left_pressed;
  bool rotate_right_pressed;
  bool rotate_left_pressed;
} t_key_status;

/*
 * 0 = X ; 1 Y
 *
 */
typedef struct s_ray {
  t_vector dir;
  t_vector map_pos;
  t_vector delta_dist;
  t_vector side_dist;
  int step_x;
  int step_y;
  int side;
  float perp_dist;
  t_texture *texture;
  float wall_x;
} t_ray;

typedef struct s_cub {
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
  int tex_x;
  float line_start_y;
  float line_end_y;
  float line_height;
} t_wall_line;

t_vector vec_add(t_vector a, t_vector b);
t_vector vec_scale(t_vector v, float scalar);
t_vector vec_normalize(t_vector v);
t_vector vec_rotate(t_vector v, float angle);
void init_cub(t_cub *cub);
void init_player(t_player *player);
void put_pixel(t_img_data *img_data, int x, int y, int color);
void render_background(t_cub *cub);
void render_walls(t_cub *cub3d);
int handle_keypress(int keycode, void *cub3d_ptr);
int game_exit(t_cub *cub);
int handle_keyrelease(int keycode, void *cub3d_ptr);
void handle_input(t_cub *cub);
int main_loop(t_cub *cub);
void load_all_textures(t_cub *cub);
bool parser_map(t_cub *cub, char *file);
void print_error_and_exit(t_cub *cub, char *msg);
void free_cub(t_cub *cub);
bool is_border_wall(t_cub *cub, int mapX, int mapY);
bool newpos_isvalid(t_cub *cub, float new_posX, float new_posY);
void move_up(t_cub *cub);
void move_down(t_cub *cub);
void move_right(t_cub *cub);
void move_left(t_cub *cub);
void rotate_right(t_cub *cub);
void rotate_left(t_cub *cub);
char *ft_remove_chars(const char *s, const char *set);
int open_file(char *file, t_cub *cub);
void pad_map_lines(char **map, int max_len);
bool validate_lines_aux(t_map *map, int *i, int *j);
void handle_color(t_cub *cub, char **chuncks, char **colors_ref, char *to_free);
void handle_texture(t_cub *cub, char **texture, char **tex, char *to_free);
void validate_map(t_cub *cub);
bool get_color_and_texture(t_cub *cub_data, t_map *map, char **elements,
                           int *i);
bool get_map(t_cub *cub_data, t_map *map, int map_height, int *i);
int count_map_height(t_cub *cub, int i);
void salt_to_first_linemap(t_map *map, int *i);
bool validate_lines2(t_map *map, int i, int j);
int is_file_empty(char *path, t_cub *cub);
bool check_cub_extension(const char *filename);
bool set_player_position(t_cub *cub, char *line, int x, int y);
void join_colors(char **chuncks, char *color, int *i);
int create_rgb(int r, int g, int b);
void put_pixel(t_img_data *img_data, int x, int y, int color);
void render_background(t_cub *cub);
t_wall_line compute_wall_line_info(t_ray *ray);
void compute_wall_data(t_cub *cub3d, t_ray *ray);
t_vector calculate_ray_direction(t_player *player, float pixel);
void step_dda(t_ray *ray, t_vector *wallMapPos);
void compute_wall_data(t_cub *cub3d, t_ray *ray);
void init_dda_aux(t_ray *ray, t_player *player);
t_cub *initialization(void);
t_vector init_vector(float x, float y);
t_player *init_player_struct(void);
t_img_data init_img_data(void);
t_texture init_texture(void);
t_map *init_map(void);
t_key_status init_key_status(void);
t_ray *init_ray(void);
t_wall_line init_wall_line(void);

#endif
