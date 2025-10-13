/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:03:24 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 23:16:00 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int	game_exit(t_cub *cub)
{
	free_cub(cub);
	exit(0);
	return (0);
}

void	handle_rotation(t_cub *cub)
{
	if (cub->key_status.rotate_right_pressed == true)
	{
		if (cub->player->orientation == 'W' || cub->player->orientation == 'S')
			rotate_left(cub);
		else if (cub->player->orientation == 'E'
			|| cub->player->orientation == 'N')
			rotate_right(cub);
	}
	if (cub->key_status.rotate_left_pressed == true)
	{
		if (cub->player->orientation == 'W' || cub->player->orientation == 'S')
			rotate_right(cub);
		else if (cub->player->orientation == 'E'
			|| cub->player->orientation == 'N')
			rotate_left(cub);
	}
}

void	handle_input(t_cub *cub)
{
	if (cub->key_status.esc_pressed == true)
		game_exit(cub);
	if (cub->key_status.move_up_pressed == true
		|| cub->key_status.move_up2_pressed == true)
		move_up(cub);
	if (cub->key_status.move_down_pressed == true
		|| cub->key_status.move_down2_pressed == true)
		move_down(cub);
	if (cub->key_status.move_right_pressed == true)
		move_right(cub);
	if (cub->key_status.move_left_pressed == true)
		move_left(cub);
	handle_rotation(cub);
}

int	handle_keypress(int keycode, void *cub3d_ptr)
{
	t_cub	*cub3d;

	cub3d = (t_cub *)cub3d_ptr;
	if (keycode == ESC)
		cub3d->key_status.esc_pressed = true;
	if (keycode == MOVE_UP)
		cub3d->key_status.move_up_pressed = true;
	if (keycode == MOVE_UP2)
		cub3d->key_status.move_up2_pressed = true;
	if (keycode == MOVE_DOWN)
		cub3d->key_status.move_down_pressed = true;
	if (keycode == MOVE_DOWN2)
		cub3d->key_status.move_down2_pressed = true;
	if (keycode == MOVE_RIGHT)
		cub3d->key_status.move_right_pressed = true;
	if (keycode == MOVE_LEFT)
		cub3d->key_status.move_left_pressed = true;
	if (keycode == ROTATE_RIGHT)
		cub3d->key_status.rotate_right_pressed = true;
	if (keycode == ROTATE_LEFT)
		cub3d->key_status.rotate_left_pressed = true;
	return (0);
}

int	handle_keyrelease(int keycode, void *cub)
{
	t_cub	*cub3d;

	cub3d = (t_cub *)cub3d_ptr;
	if (keycode == ESC)
		cub3d->key_status.esc_pressed = false;
	if (keycode == MOVE_UP)
		cub3d->key_status.move_up_pressed = false;
	if (keycode == MOVE_UP2)
		cub3d->key_status.move_up2_pressed = false;
	if (keycode == MOVE_DOWN)
		cub3d->key_status.move_down_pressed = false;
	if (keycode == MOVE_DOWN2)
		cub3d->key_status.move_down2_pressed = false;
	if (keycode == MOVE_RIGHT)
		cub3d->key_status.move_right_pressed = false;
	if (keycode == MOVE_LEFT)
		cub3d->key_status.move_left_pressed = false;
	if (keycode == ROTATE_RIGHT)
		cub3d->key_status.rotate_right_pressed = false;
	if (keycode == ROTATE_LEFT)
		cub3d->key_status.rotate_left_pressed = false;
	return (0);
}
