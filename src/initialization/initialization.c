/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:03:36 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 23:17:45 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	init_player(t_player *player)
{
	player->move_speed = 0.009999;
	player->rot_speed = 0.009;
}

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		print_error_and_exit(cub, "Error to start MiniLibX");
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!cub->win)
		print_error_and_exit(cub, "Error to open window");
	cub->img_data.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img_data.img)
		print_error_and_exit(cub, "Error to create image");
	cub->img_data.addr = mlx_get_data_addr(cub->img_data.img,
			&cub->img_data.bpp, &cub->img_data.line_len, &cub->img_data.endian);
	if (!cub->img_data.addr)
		print_error_and_exit(cub, "Error to get addr");
}

void	init_cub(t_cub *cub)
{
	init_mlx(cub);
	init_player(cub->player);
	load_all_textures(cub);
}

t_cub	*initialization(void)
{
	t_cub	*c;
	int		i;

	c = malloc(sizeof(t_cub));
	if (!c)
		return (NULL);
	c->mlx = NULL;
	c->win = NULL;
	c->img_data = init_img_data();
	c->player = init_player_struct();
	c->map = init_map();
	c->key_status = init_key_status();
	c->ray = init_ray();
	i = 0;
	while (i < 4)
	{
		c->textures[i] = init_texture();
		i++;
	}
	return (c);
}
