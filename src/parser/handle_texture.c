/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:53:33 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/12 05:31:59 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static void	load_texture(t_cub *cub, t_texture *texture, char *relative_path,
				int index);

void	handle_texture(t_cub *cub, char **texture, char **tex, char *to_free)
{
	int	elements_len;

	elements_len = ft_count_matrix(texture);
	if (elements_len != 2)
	{
		free(to_free);
		ft_free_matrix(texture);
		print_error_and_exit(cub, "Texture error: invalid value");
	}
	if (*tex)
	{
		free(to_free);
		ft_free_matrix(texture);
		print_error_and_exit(cub, "Duplicated texture");
	}
	else
		*tex = ft_strdup(texture[1]);
}

void	load_all_textures(t_cub *cub)
{
	load_texture(cub, &cub->textures[NORTH], cub->map->NO, NORTH);
	load_texture(cub, &cub->textures[SOUTH], cub->map->SO, SOUTH);
	load_texture(cub, &cub->textures[EAST], cub->map->EA, EAST);
	load_texture(cub, &cub->textures[WEST], cub->map->WE, WEST);
}

static void	load_texture(t_cub *cub, t_texture *texture, char *relative_path,
		int index)
{
	if (!cub->mlx)
		print_error_and_exit(cub, "Faile: minilibx not initialized");
	texture->img = mlx_xpm_file_to_image(cub->mlx, relative_path,
			&texture->width, &texture->height);
	if (!texture->img)
		print_error_and_exit(cub, "Texture invalid");
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	if (!texture->addr)
		print_error_and_exit(cub, "Texture invalid");
	cub->textures[index] = *texture;
}
