/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:03:24 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/08 11:03:26 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int game_exit(t_cub *cub) {
  free_cub(cub);
  exit(0);
  return (0);
}

void handle_input(t_cub *cub) {
  if (cub->key_status.ESC_PRESSED == true)
    game_exit(cub);
  if (cub->key_status.MOVE_UP_PRESSED == true ||
      cub->key_status.MOVE_UP2_PRESSED == true)
    move_up(cub);
  if (cub->key_status.MOVE_DOWN_PRESSED == true ||
      cub->key_status.MOVE_DOWN2_PRESSED == true)
    move_down(cub);
  if (cub->key_status.MOVE_RIGHT_PRESSED == true)
    move_right(cub);
  if (cub->key_status.MOVE_LEFT_PRESSED == true)
    move_left(cub);
  if (cub->key_status.ROTATE_RIGHT_PRESSED == true)
    rotate_right(cub);
  if (cub->key_status.ROTATE_LEFT_PRESSED == true)
    rotate_left(cub);
}

int handle_keypress(int keycode, void *cub3d_ptr) {
  t_cub *cub3d;

  cub3d = (t_cub *)cub3d_ptr;
  if (keycode == ESC)
    cub3d->key_status.ESC_PRESSED = true;
  if (keycode == MOVE_UP)
    cub3d->key_status.MOVE_UP_PRESSED = true;
  if (keycode == MOVE_UP2)
    cub3d->key_status.MOVE_UP2_PRESSED = true;
  if (keycode == MOVE_DOWN)
    cub3d->key_status.MOVE_DOWN_PRESSED = true;
  if (keycode == MOVE_DOWN2)
    cub3d->key_status.MOVE_DOWN2_PRESSED = true;
  if (keycode == MOVE_RIGHT)
    cub3d->key_status.MOVE_RIGHT_PRESSED = true;
  if (keycode == MOVE_LEFT)
    cub3d->key_status.MOVE_LEFT_PRESSED = true;
  if (keycode == ROTATE_RIGHT)
    cub3d->key_status.ROTATE_RIGHT_PRESSED = true;
  if (keycode == ROTATE_LEFT)
    cub3d->key_status.ROTATE_LEFT_PRESSED = true;
  return (0);
}

int handle_keyrelease(int keycode, void *cub3d_ptr) {
  t_cub *cub3d;

  cub3d = (t_cub *)cub3d_ptr;
  if (keycode == ESC)
    cub3d->key_status.ESC_PRESSED = false;
  if (keycode == MOVE_UP)
    cub3d->key_status.MOVE_UP_PRESSED = false;
  if (keycode == MOVE_UP2)
    cub3d->key_status.MOVE_UP2_PRESSED = false;
  if (keycode == MOVE_DOWN)
    cub3d->key_status.MOVE_DOWN_PRESSED = false;
  if (keycode == MOVE_DOWN2)
    cub3d->key_status.MOVE_DOWN2_PRESSED = false;
  if (keycode == MOVE_RIGHT)
    cub3d->key_status.MOVE_RIGHT_PRESSED = false;
  if (keycode == MOVE_LEFT)
    cub3d->key_status.MOVE_LEFT_PRESSED = false;
  if (keycode == ROTATE_RIGHT)
    cub3d->key_status.ROTATE_RIGHT_PRESSED = false;
  if (keycode == ROTATE_LEFT)
    cub3d->key_status.ROTATE_LEFT_PRESSED = false;
  return (0);
}
