/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 23:59:50 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 00:19:42 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int	create_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	put_pixel(t_img_data *img_data, int x, int y, int color)
{
	int	offset;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		offset = (y * img_data->line_len) + (x * (img_data->bpp / 8));
		*(unsigned int *)(img_data->addr + offset) = color;
	}
}

t_vector	calculate_ray_direction(t_player *player, float pixel)
{
	float		multiplier;
	t_vector	camera_pixel;
	t_vector	ray_dir;

	multiplier = 2 * (pixel / (double)WIDTH) - 1;
	camera_pixel = vec_scale(player->plane, multiplier);
	ray_dir = vec_add(player->dir, camera_pixel);
	return (ray_dir);
}

void	step_dda(t_ray *ray, t_vector *wallMapPos)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		wallMapPos->x += ray->step_x;
		ray->side_dist.x += ray->delta_dist.x;
		ray->side = 0;
	}
	else
	{
		wallMapPos->y += ray->step_y;
		ray->side_dist.y += ray->delta_dist.y;
		ray->side = 1;
	}
}
