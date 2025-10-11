/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_and_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:04:05 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/10 17:16:04 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

static void free_map(t_map *map);

void free_cub(t_cub *cub) {
  int i;

  if (!cub)
    return;

  i = 0;
  while (i < 4) {
    if (cub->textures[i].img)
      mlx_destroy_image(cub->mlx, cub->textures[i].img);
    i++;
  }

  if (cub->img_data.img)
    mlx_destroy_image(cub->mlx, cub->img_data.img);

  if (cub->player)
    free(cub->player);

  if (cub->map)
    free_map(cub->map);

  if (cub->ray)
    free(cub->ray);

  if (cub->win)
    mlx_destroy_window(cub->mlx, cub->win);

  if (cub->mlx) {
    mlx_destroy_display(cub->mlx);
    free(cub->mlx);
  }

  free(cub);
}

void print_error_and_exit(t_cub *cub, char *msg) {
  (void)cub;
  char *fullMessage;

  free_cub(cub);
  fullMessage = ft_strjoin("Error\n", msg);
  ft_putendl_fd(fullMessage, 2);
  free(fullMessage);
  exit(0);
}

static void free_map(t_map *map) {
  int i;

  if (!map)
    return;

  if (map->map_raw_datas) {
    i = 0;
    while (map->map_raw_datas[i]) {
      free(map->map_raw_datas[i]);
      i++;
    }
    free(map->map_raw_datas);
  }

  free(map->NO);
  free(map->SO);
  free(map->WE);
  free(map->EA);

  ft_free_matrix(map->C);
  ft_free_matrix(map->F);

  free(map);
}
