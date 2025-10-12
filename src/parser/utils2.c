/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:50:57 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/12 20:51:51 by mmorais          ###   ########.fr       */
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
