/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_position.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:05:15 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/11 12:03:22 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

bool	is_border_wall(t_cub *cub, int mapX, int mapY)
{
	int	map_height;
	int	line_len;

	map_height = 0;
	while (cub->map->gamemap[map_height])
		map_height++;
	if (mapY < 0 || mapY >= map_height)
		return (true);
	line_len = strlen(cub->map->gamemap[mapY]);
	if (mapX < 0 || mapX >= line_len)
		return (true);
	if (mapY == 0 || mapY == map_height - 1)
		return (true);
	if (mapX == 0 || mapX == line_len - 1)
		return (true);
	return (false);
}

bool	newpos_isvalid(t_cub *cub, float new_posX, float new_posY)
{
	int		new_mapX;
	int		new_mapY;
	int		map_height;
	int		line_len;
	char	tile;

	new_mapX = (int)new_posX;
	new_mapY = (int)new_posY;
	map_height = 0;
	while (cub->map->gamemap[map_height])
		map_height++;
	if (new_mapY < 0 || new_mapY >= map_height)
		return (false);
	line_len = strlen(cub->map->gamemap[new_mapY]);
	if (new_mapX < 0 || new_mapX >= line_len)
		return (false);
	tile = cub->map->gamemap[new_mapY][new_mapX];
	if (!(tile == '1' && is_border_wall(cub, new_mapX, new_mapY)))
		return (true);
	return (false);
}
