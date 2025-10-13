/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <zombunga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:50:57 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 16:51:40 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

bool	validate_lines_aux(t_map *map, int *i, int *j)
{
	while (map->gamemap[*i][*j] != '\0')
	{
		if (map->gamemap[*i][*j] != ' ' && map->gamemap[*i][*j] != '0'
			&& map->gamemap[*i][*j] != '1' && map->gamemap[*i][*j] != 'N'
			&& map->gamemap[*i][*j] != 'S' && map->gamemap[*i][*j] != 'E'
			&& map->gamemap[*i][*j] != 'W')
		{
			return (false);
		}
		if (map->gamemap[*i][*j] == ' ')
		{
			if (validate_lines2(map, *i, *j) == false)
				return (false);
		}
		(*j)++;
	}
	return (true);
}

bool	set_player_position(t_cub *cub, char *line, int x, int y)
{
	if (line[x] == 'N' || line[x] == 'S' || line[x] == 'E' || line[x] == 'W')
	{
		if (cub->player->pos.x)
			return (false);
		cub->player->pos.x = x + 0.5;
		cub->player->pos.y = y + 0.5;
		cub->map->gamemap[y][x] = '0';
	}
	if(line[x] == 'N'){
		cub->player->dir = (t_vector){0, -1};
		cub->player->plane = (t_vector){0.66, 0};
	}
	else if(line[x] == 'S'){
		cub->player->dir = (t_vector){0, 1};
		cub->player->plane = (t_vector){0.66, 0};
	}
	else if(line[x] == 'E'){
		cub->player->dir = (t_vector){1, 0};
		cub->player->plane = (t_vector){0, 0.66};
	}
	else if(line[x] == 'W'){
		cub->player->dir = (t_vector){-1, 0};
		cub->player->plane = (t_vector){0, 0.66};
	}
	return (true);
}
