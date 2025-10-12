/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:00:03 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/12 20:47:05 by mmorais          ###   ########.fr       */
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

void	render_background(t_cub *cub)
{
	int	C0;
	int	C1;
	int	C2;
	int	F0;
	int	F1;
	int	F2;
	int	SKY_COLOR;
	int	GROUND_COLOR;
	int	y;
	int	x;
	int	color;

	C0 = ft_atoi(cub->map->C[0]);
	C1 = ft_atoi(cub->map->C[1]);
	C2 = ft_atoi(cub->map->C[2]);
	F0 = ft_atoi(cub->map->F[0]);
	F1 = ft_atoi(cub->map->F[1]);
	F2 = ft_atoi(cub->map->F[2]);
	SKY_COLOR = create_rgb(C0, C1, C2);
	GROUND_COLOR = create_rgb(F0, F1, F2);
	y = 0;
	while (y < HEIGHT)
	{
		if (y < HEIGHT / 2)
			color = SKY_COLOR;
		else
			color = GROUND_COLOR;
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(&cub->img_data, x, y, color);
			x++;
		}
		y++;
	}
}

t_vector	calculate_ray_direction(t_player *player, float pixel)
{
	float		multiplier;
	t_vector	cameraPixel;
	t_vector	rayDir;

	multiplier = 2 * (pixel / (double)WIDTH) - 1;
	cameraPixel = vec_scale(player->plane, multiplier);
	rayDir = vec_add(player->dir, cameraPixel);
	return (rayDir);
}

void	init_dda(t_ray *ray, t_player *player)
{
	ray->delta_dist.x = (ray->dir.x == 0) ? 1e30 : fabs(1.0 / ray->dir.x);
	ray->delta_dist.y = (ray->dir.y == 0) ? 1e30 : fabs(1.0 / ray->dir.y);
	ray->map_pos = (t_vector){floor(player->pos.x), floor(player->pos.y)};
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

void	execute_dda(t_cub *cub3d, t_ray *ray)
{
	bool		hit;
	t_vector	wallMapPos;

	hit = false;
	wallMapPos = (t_vector){ray->map_pos.x, ray->map_pos.y};
	while (hit == false)
	{
		step_dda(ray, &wallMapPos);
		if ((int)wallMapPos.y >= 0 && (int)wallMapPos.y < cub3d->map->height
			&& (int)wallMapPos.x >= 0 && (int)wallMapPos.x < cub3d->map->width)
		{
			if (cub3d->map->gamemap[(int)wallMapPos.y][(int)wallMapPos.x] > '0')
			{
				hit = true;
			}
		}
		else
		{
			hit = true;
		}
		if (wallMapPos.y < 0.25 || wallMapPos.x < 0.25
			|| wallMapPos.y > cub3d->map->height - 0.25
			|| wallMapPos.x > cub3d->map->width - 1.25)
			break ;
		else if (cub3d->map->gamemap[(int)wallMapPos.y][(int)wallMapPos.x] > '0')
			hit = true;
	}
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

void	draw_wall_line(t_cub *cub3d, t_ray *ray, int pixel)
{
	t_wall_line		info;
	int				texY;
	int				offset_tex;
	unsigned int	wallColor;

	info = compute_wall_line_info(ray);
	for (int y_coord = info.start; y_coord <= info.end; y_coord++)
	{
		texY = (int)(((y_coord - info.line_start_y) / (info.line_end_y
						- info.line_start_y)) * ray->texture->height);
		if (texY < 0)
			texY = 0;
		if (texY > ray->texture->height)
			texY = ray->texture->height - 1;
		offset_tex = (texY * ray->texture->line_len) + (info.texX
				* (ray->texture->bpp / 8));
		wallColor = *(unsigned int *)(ray->texture->addr + offset_tex);
		put_pixel(&cub3d->img_data, (int)pixel, y_coord, wallColor);
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
		execute_dda(cub3d, ray);
		compute_wall_data(cub3d, ray);
		draw_wall_line(cub3d, ray, pixel);
		pixel++;
	}
}
