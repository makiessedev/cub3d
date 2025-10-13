/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:05:25 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 05:23:27 by mmorais          ###   ########.fr       */
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

	cub = initialization();
	if (ac != 2)
		print_error_and_exit(cub, "Invalid arguments");
	if (!check_cub_extension(av[1]))
		print_error_and_exit(cub, "Invalid file extension. Expected .cub");
	if (parser_map(cub, av[1]) == false)
		print_error_and_exit(cub, "Invalid Map");
	init_cub(cub);
	mlx_loop_hook(cub->mlx, &main_loop, cub);
	mlx_hook(cub->win, DESTROY_NOTIFY, IGNORE_MASK, &game_exit, cub);
	mlx_hook(cub->win, KEYPRESS, 1L << 0, &handle_keypress, cub);
	mlx_hook(cub->win, KEYRELEASE, 1L << 1, &handle_keyrelease, cub);
	mlx_loop(cub->mlx);
	return (0);
}
