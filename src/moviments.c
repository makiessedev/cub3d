/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moviments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:03:58 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 00:20:21 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	move_up(t_cub *cub)
{
	float	new_pos_x;
	float	new_pos_y;

	new_pos_x = cub->player->pos.x + cub->player->dir.x
		* cub->player->move_speed;
	new_pos_y = cub->player->pos.y + cub->player->dir.y
		* cub->player->move_speed;
	if (cub->map->gamemap[(int)cub->player->pos.y][(int)new_pos_x] == '0')
		cub->player->pos.x = new_pos_x;
	if (cub->map->gamemap[(int)new_pos_y][(int)cub->player->pos.x] == '0')
		cub->player->pos.y = new_pos_y;
}

void	move_down(t_cub *cub)
{
	float	new_pos_x;
	float	new_pos_y;

	new_pos_x = cub->player->pos.x - cub->player->dir.x
		* cub->player->move_speed;
	new_pos_y = cub->player->pos.y - cub->player->dir.y
		* cub->player->move_speed;
	if (cub->map->gamemap[(int)cub->player->pos.y][(int)new_pos_x] == '0')
		cub->player->pos.x = new_pos_x;
	if (cub->map->gamemap[(int)new_pos_y][(int)cub->player->pos.x] == '0')
		cub->player->pos.y = new_pos_y;
}

void	move_right(t_cub *cub)
{
	float	new_pos_x;
	float	new_pos_y;

	new_pos_x = cub->player->pos.x + cub->player->plane.x
		* cub->player->move_speed;
	new_pos_y = cub->player->pos.y + cub->player->plane.y
		* cub->player->move_speed;
	if (cub->map->gamemap[(int)cub->player->pos.y][(int)new_pos_x] == '0')
		cub->player->pos.x = new_pos_x;
	if (cub->map->gamemap[(int)new_pos_y][(int)cub->player->pos.x] == '0')
		cub->player->pos.y = new_pos_y;
}

void	move_left(t_cub *cub)
{
	float	new_pos_x;
	float	new_pos_y;

	new_pos_x = cub->player->pos.x - cub->player->plane.x
		* cub->player->move_speed;
	new_pos_y = cub->player->pos.y - cub->player->plane.y
		* cub->player->move_speed;
	if (cub->map->gamemap[(int)cub->player->pos.y][(int)new_pos_x] == '0')
		cub->player->pos.x = new_pos_x;
	if (cub->map->gamemap[(int)new_pos_y][(int)cub->player->pos.x] == '0')
		cub->player->pos.y = new_pos_y;
}
