/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:17:59 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 23:18:42 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	render_background(t_cub *cub)
{
	int	sky_color;
	int	ground_color;
	int	y;
	int	x;
	int	color;

	sky_color = create_rgb(ft_atoi(cub->map->c[0]), ft_atoi(cub->map->c[1]),
			ft_atoi(cub->map->c[2]));
	ground_color = create_rgb(ft_atoi(cub->map->f[0]), ft_atoi(cub->map->f[1]),
			ft_atoi(cub->map->f[2]));
	y = 0;
	while (y < HEIGHT)
	{
		if (y < HEIGHT / 2)
			color = sky_color;
		else
			color = ground_color;
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(&cub->img_data, x, y, color);
			x++;
		}
		y++;
	}
}

t_wall_line	compute_wall_line_info(t_ray *ray)
{
	t_wall_line	info;

	info.line_height = HEIGHT / ray->perp_dist;
	info.line_start_y = (float)HEIGHT / 2 - info.line_height / 2;
	info.line_end_y = (float)HEIGHT / 2 + info.line_height / 2;
	info.start = (int)info.line_start_y;
	info.end = (int)info.line_end_y;
	if (info.start < 0)
		info.start = 0;
	if (info.end >= HEIGHT)
		info.end = HEIGHT - 1;
	info.tex_x = (int)(ray->wall_x * (float)ray->texture->width);
	return (info);
}

void	init_dda_aux(t_ray *ray, t_player *player)
{
	if (ray->dir.x < 0)
	{
		ray->side_dist.x = (player->pos.x - ray->map_pos.x) * ray->delta_dist.x;
		ray->step_x = -1;
	}
	else
	{
		ray->side_dist.x = (ray->map_pos.x + 1 - player->pos.x)
			* ray->delta_dist.x;
		ray->step_x = 1;
	}
	if (ray->dir.y < 0)
	{
		ray->side_dist.y = (player->pos.y - ray->map_pos.y) * ray->delta_dist.y;
		ray->step_y = -1;
	}
	else
	{
		ray->side_dist.y = (ray->map_pos.y + 1 - player->pos.y)
			* ray->delta_dist.y;
		ray->step_y = 1;
	}
}
