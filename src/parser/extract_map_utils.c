/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:53:20 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/11 12:01:59 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int	count_map_height(t_cub *cub, int i)
{
	int		map_hight;
	char	*line;

	map_hight = 0;
	while (cub->map->map_raw_datas[i])
	{
		line = ft_strtrim(cub->map->map_raw_datas[i], M_EMPTY);
		if (line[0] == '\0')
		{
			free(line);
			i++;
			continue ;
		}
		if (line[0] != '1')
		{
			free(line);
			print_error_and_exit(cub, "Invalid Map");
		}
		free(line);
		map_hight++;
		i++;
	}
	return (map_hight);
}

void	salt_to_first_linemap(t_map *map, int *i)
{
	char	*line;

	line = ft_strtrim(map->map_raw_datas[*i], M_EMPTY);
	while (line[0] == '\0')
	{
		free(line);
		(*i)++;
		line = ft_strtrim(map->map_raw_datas[*i], M_EMPTY);
	}
	free(line);
}
