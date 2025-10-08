/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:04:29 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/08 11:04:30 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	rotate_right(t_cub *cub)
{
	cub->player->dir = vec_rotate(cub->player->dir, -cub->player->rot_speed);
	cub->player->plane = vec_rotate(cub->player->plane,
			-cub->player->rot_speed);
}

void	rotate_left(t_cub *cub)
{
	cub->player->dir = vec_rotate(cub->player->dir, cub->player->rot_speed);
	cub->player->plane = vec_rotate(cub->player->plane, cub->player->rot_speed);
}
