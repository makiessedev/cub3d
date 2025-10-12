/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:17:59 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 00:28:01 by mmorais          ###   ########.fr       */
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
