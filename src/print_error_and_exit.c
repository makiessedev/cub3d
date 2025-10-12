/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_and_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:04:05 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 00:25:10 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

static void	free_map(t_map *map);

void	free_cub_aux(t_cub *cub)
{
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
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
}

void	free_cub(t_cub *cub)
{
	int	i;

	if (!cub)
		return ;
	i = 0;
	while (i < 4)
	{
		if (cub->textures[i].img)
			mlx_destroy_image(cub->mlx, cub->textures[i].img);
		i++;
	}
	free_cub_aux(cub);
	free(cub);
}

void	print_error_and_exit(t_cub *cub, char *msg)
{
	char	*full_message;

	(void)cub;
	free_cub(cub);
	full_message = ft_strjoin("Error\n", msg);
	ft_putendl_fd(full_message, 2);
	free(full_message);
	exit(0);
}

static void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	ft_free_matrix(map->gamemap);
	ft_free_matrix(map->map_raw_datas);
	free(map->NO);
	free(map->SO);
	free(map->WE);
	free(map->EA);
	i = 0;
	while (i < 3)
	{
		free(map->F[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		free(map->C[i]);
		i++;
	}
	free(map);
}
