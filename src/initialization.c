/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <zombunga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:03:36 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 17:05:05 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	init_player(t_player *player)
{
	player->move_speed = 0.009999;
	player->rot_speed = 0.009;
}

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		print_error_and_exit(cub, "Error to start MiniLibX");
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!cub->win)
		print_error_and_exit(cub, "Error to open window");
	cub->img_data.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img_data.img)
		print_error_and_exit(cub, "Error to create image");
	cub->img_data.addr = mlx_get_data_addr(cub->img_data.img,
			&cub->img_data.bpp, &cub->img_data.line_len, &cub->img_data.endian);
	if (!cub->img_data.addr)
		print_error_and_exit(cub, "Error to get addr");
}

void	init_cub(t_cub *cub)
{
	init_mlx(cub);
	init_player(cub->player);
	load_all_textures(cub);
}

t_vector	init_vector(float x, float y)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_player	*init_player_struct()
{
	t_player	*p;

	p = malloc(sizeof(t_player));
	if (!p)
		return (NULL);
	p->pos = init_vector(0, 0);
	p->dir = init_vector(0, 0);
	p->plane = init_vector(0, 0);
	p->move_speed = 0.05f;
	p->rot_speed = 0.05f;
	p->orientation = 'N';
	return (p);
}

t_img_data	init_img_data()
{
	t_img_data	img;

	img.img = NULL;
	img.addr = NULL;
	img.bpp = 0;
	img.line_len = 0;
	img.endian = 0;
	return (img);
}

t_texture	init_texture(void)
{
	t_texture	tex;

	tex.img = NULL;
	tex.addr = NULL;
	tex.width = 0;
	tex.height = 0;
	tex.bpp = 0;
	tex.line_len = 0;
	tex.endian = 0;
	return (tex);
}

t_map	*init_map(void)
{
	t_map	*m;
	int		i;

	m = malloc(sizeof(t_map));
	if (!m)
		return (NULL);
	m->map_raw_datas = NULL;
	m->map_path = NULL;
	m->gamemap = NULL;
	m->width = 0;
	m->height = 0;
	m->so = NULL;
	m->no = NULL;
	m->we = NULL;
	m->ea = NULL;
	i = 0;
	while (i < 3)
	{
		m->f[i] = NULL;
		m->c[i] = NULL;
		i++;
	}
	return (m);
}

t_key_status	init_key_status(void)
{
	t_key_status	k;

	k.esc_pressed = false;
	k.move_up_pressed = false;
	k.move_up2_pressed = false;
	k.move_down_pressed = false;
	k.move_down2_pressed = false;
	k.move_right_pressed = false;
	k.move_left_pressed = false;
	k.rotate_right_pressed = false;
	k.rotate_left_pressed = false;
	return (k);
}

t_ray	*init_ray(void)
{
	t_ray	*r;

	r = malloc(sizeof(t_ray));
	if (!r)
		return (NULL);
	r->dir = init_vector(0, 0);
	r->map_pos = init_vector(0, 0);
	r->delta_dist = init_vector(0, 0);
	r->side_dist = init_vector(0, 0);
	r->step_x = 0;
	r->step_y = 0;
	r->side = 0;
	r->perp_dist = 0;
	r->texture = NULL;
	r->wall_x = 0;
	return (r);
}

t_wall_line	init_wall_line(void)
{
	t_wall_line	w;

	w.start = 0;
	w.end = 0;
	w.tex_x = 0;
	w.line_start_y = 0;
	w.line_end_y = 0;
	w.line_height = 0;
	return (w);
}

t_cub	*initialization(void)
{
	t_cub	*c;
	int		i;

	c = malloc(sizeof(t_cub));
	if (!c)
		return (NULL);
	c->mlx = NULL;
	c->win = NULL;
	c->img_data = init_img_data();
	c->player = init_player_struct();
	c->map = init_map();
	c->key_status = init_key_status();
	c->ray = init_ray();
	i = 0;
	while (i < 4)
	{
		c->textures[i] = init_texture();
		i++;
	}
	return (c);
}