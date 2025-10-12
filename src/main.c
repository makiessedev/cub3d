/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:05:25 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/11 12:02:52 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int	main_loop(t_cub *cub)
{
	handle_input(cub);
	render_background(cub);
	render_walls(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img_data.img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	cub->map = malloc(sizeof(t_map));
	cub->player = malloc(sizeof(t_player));
	cub->ray = malloc(sizeof(t_ray));
	if (ac != 2)
		print_error_and_exit(cub, "Invalid arguments");
	if (!check_cub_extension(av[1]))
		print_error_and_exit(cub, "Invalid file extension. Expected .cub");
	if (parser_map(cub, av[1]) == false)
		print_error_and_exit(cub, "Invalid Map");
	init_cub(cub);
	mlx_loop_hook(cub->mlx, &main_loop, cub);
	mlx_hook(cub->win, DESTROY_NOTIFY, IGNORE_MASK, &game_exit, cub);
	mlx_hook(cub->win, KEYPRESS, KEYPRESS_MASK, &handle_keypress, cub);
	mlx_hook(cub->win, KEYRELEASE, KEYRELEASE_MASK, &handle_keyrelease, cub);
	mlx_loop(cub->mlx);
	return (0);
}
