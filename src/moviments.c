/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moviments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:03:58 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/12 20:26:31 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	move_up(t_cub *cub)
{
	float	new_posX;
	float	new_posY;

	new_posX = cub->player->pos.x + cub->player->dir.x
		* cub->player->move_speed;
	new_posY = cub->player->pos.y + cub->player->dir.y
		* cub->player->move_speed;
	if (cub->map->gamemap[(int)cub->player->pos.y][(int)new_posX] == '0')
		cub->player->pos.x = new_posX;
	if (cub->map->gamemap[(int)new_posY][(int)cub->player->pos.x] == '0')
		cub->player->pos.y = new_posY;
}

void	move_down(t_cub *cub)
{
	float	new_posX;
	float	new_posY;

	new_posX = cub->player->pos.x - cub->player->dir.x
		* cub->player->move_speed;
	new_posY = cub->player->pos.y - cub->player->dir.y
		* cub->player->move_speed;
	if (cub->map->gamemap[(int)cub->player->pos.y][(int)new_posX] == '0')
		cub->player->pos.x = new_posX;
	if (cub->map->gamemap[(int)new_posY][(int)cub->player->pos.x] == '0')
		cub->player->pos.y = new_posY;
}

void	move_right(t_cub *cub)
{
	float	new_posX;
	float	new_posY;

	new_posX = cub->player->pos.x + cub->player->plane.x
		* cub->player->move_speed;
	new_posY = cub->player->pos.y + cub->player->plane.y
		* cub->player->move_speed;
	if (cub->map->gamemap[(int)cub->player->pos.y][(int)new_posX] == '0')
		cub->player->pos.x = new_posX;
	if (cub->map->gamemap[(int)new_posY][(int)cub->player->pos.x] == '0')
		cub->player->pos.y = new_posY;
}

void	move_left(t_cub *cub)
{
	float	new_posX;
	float	new_posY;

	new_posX = cub->player->pos.x - cub->player->plane.x
		* cub->player->move_speed;
	new_posY = cub->player->pos.y - cub->player->plane.y
		* cub->player->move_speed;
	if (cub->map->gamemap[(int)cub->player->pos.y][(int)new_posX] == '0')
		cub->player->pos.x = new_posX;
	if (cub->map->gamemap[(int)new_posY][(int)cub->player->pos.x] == '0')
		cub->player->pos.y = new_posY;
}
