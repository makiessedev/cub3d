/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <zombunga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:17:59 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 18:08:54 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

static void	handle_vertical_wall(t_cub *cub3d, t_ray *ray);
static void	handle_horizontal_wall(t_cub *cub3d, t_ray *ray);

void	compute_wall_data(t_cub *cub3d, t_ray *ray)
{
	if (ray->side == 0)
		handle_vertical_wall(cub3d, ray);
	else
		handle_horizontal_wall(cub3d, ray);
	ray->wall_x -= floor(ray->wall_x);
}

static void	handle_vertical_wall(t_cub *cub3d, t_ray *ray)
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

static void	handle_horizontal_wall(t_cub *cub3d, t_ray *ray)
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
