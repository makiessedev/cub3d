/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:17:59 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 00:18:00 by mmorais          ###   ########.fr       */
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

	sky_color = create_rgb(ft_atoi(cub->map->C[0]), ft_atoi(cub->map->C[1]),
			ft_atoi(cub->map->C[2]));
	ground_color = create_rgb(ft_atoi(cub->map->F[0]), ft_atoi(cub->map->F[1]),
			ft_atoi(cub->map->F[2]));
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
	info.texX = (int)(ray->wall_x * (float)ray->texture->width);
	return (info);
}

void	compute_wall_data(t_cub *cub3d, t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->perp_dist = ray->side_dist.x - ray->delta_dist.x;
		ray->wall_x = cub3d->player->pos.y + ray->perp_dist * ray->dir.y;
		if (ray->dir.x > 0)
		{
			ray->texture = &cub3d->textures[WEST];
		}
		else
		{
			ray->texture = &cub3d->textures[EAST];
		}
	}
	else
	{
		ray->perp_dist = ray->side_dist.y - ray->delta_dist.y;
		ray->wall_x = cub3d->player->pos.x + ray->perp_dist * ray->dir.x;
		if (ray->dir.y > 0)
		{
			ray->texture = &cub3d->textures[NORTH];
		}
		else
		{
			ray->texture = &cub3d->textures[SOUTH];
		}
	}
	ray->wall_x -= floor(ray->wall_x);
}
