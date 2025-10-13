/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:03:36 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 23:18:07 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

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
