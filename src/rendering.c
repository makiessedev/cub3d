/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:00:03 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 00:35:43 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	init_dda(t_ray *ray, t_player *player)
{
	if (ray->dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1.0 / ray->dir.y);
	ray->map_pos = (t_vector){floor(player->pos.x), floor(player->pos.y)};
	init_dda_aux(ray, player);
}

void	execute_dda(t_cub *cub3d, t_map *map, t_ray *ray)
{
	bool		hit;
	t_vector	wall_map_pos;

	hit = false;
	wall_map_pos = (t_vector){ray->map_pos.x, ray->map_pos.y};
	while (hit == false)
	{
		step_dda(ray, &wall_map_pos);
		if ((int)wall_map_pos.y >= 0 && (int)wall_map_pos.y < cub3d->map->height
			&& (int)wall_map_pos.x >= 0
			&& (int)wall_map_pos.x < cub3d->map->width)
		{
			if (map->gamemap[(int)wall_map_pos.y][(int)wall_map_pos.x] > '0')
				hit = true;
		}
		else
			hit = true;
		if (wall_map_pos.y < 0.25 || wall_map_pos.x < 0.25
			|| wall_map_pos.y > cub3d->map->height - 0.25
			|| wall_map_pos.x > cub3d->map->width - 1.25)
			break ;
		else if (map->gamemap[(int)wall_map_pos.y][(int)wall_map_pos.x] > '0')
			hit = true;
	}
}

void	draw_wall_line(t_cub *cub3d, t_ray *ray, int pixel)
{
	t_wall_line		info;
	int				tex_y;
	int				offset_tex;
	unsigned int	wall_color;
	int				y_coord;

	info = compute_wall_line_info(ray);
	y_coord = info.start;
	while (y_coord <= info.end)
	{
		tex_y = (int)(((y_coord - info.line_start_y) / (info.line_end_y
						- info.line_start_y)) * ray->texture->height);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y > ray->texture->height)
			tex_y = ray->texture->height - 1;
		offset_tex = (tex_y * ray->texture->line_len) + (info.texX
				* (ray->texture->bpp / 8));
		wall_color = *(unsigned int *)(ray->texture->addr + offset_tex);
		put_pixel(&cub3d->img_data, (int)pixel, y_coord, wall_color);
		y_coord++;
	}
}

void	render_walls(t_cub *cub3d)
{
	float	pixel;
	t_ray	*ray;

	pixel = 0;
	while (pixel < WIDTH)
	{
		cub3d->ray->dir = calculate_ray_direction(cub3d->player, pixel);
		ray = cub3d->ray;
		init_dda(ray, cub3d->player);
		execute_dda(cub3d, cub3d->map, ray);
		compute_wall_data(cub3d, ray);
		draw_wall_line(cub3d, ray, pixel);
		pixel++;
	}
}
