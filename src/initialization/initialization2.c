/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:03:36 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 23:17:33 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

t_vector	init_vector(float x, float y)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_player	*init_player_struct(void)
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

t_img_data	init_img_data(void)
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
