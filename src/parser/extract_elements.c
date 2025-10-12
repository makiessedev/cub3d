/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:53:14 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/11 12:01:55 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

bool	get_color_and_texture(t_cub *cub_data, t_map *map, char **elements,
		int *i)
{
	char	*key;
	int		elements_len;

	key = ft_strtrim(elements[0], M_EMPTY);
	elements_len = ft_count_matrix(elements);
	if (!ft_strncmp(key, M_NO, ft_strlen(key)))
		handle_texture(cub_data, elements, elements_len, &(map->NO), key);
	else if (!ft_strncmp(key, M_SO, ft_strlen(key)))
		handle_texture(cub_data, elements, elements_len, &(map->SO), key);
	else if (!ft_strncmp(key, M_WE, ft_strlen(key)))
		handle_texture(cub_data, elements, elements_len, &(map->WE), key);
	else if (!ft_strncmp(key, M_EA, ft_strlen(key)))
		handle_texture(cub_data, elements, elements_len, &(map->EA), key);
	else if (!ft_strncmp(key, M_FLOOR, ft_strlen(key)))
		handle_color(cub_data, elements, elements_len, map->F, key);
	else if (!ft_strncmp(key, M_CEIL, ft_strlen(key)))
		handle_color(cub_data, elements, elements_len, map->C, key);
	else
	{
		free(key);
		return (false);
	}
	free(key);
	if (map->NO && map->SO && map->WE && map->EA && map->C[0] && map->F[0])
		(*i)++;
	return (true);
}

bool	get_map(t_cub *cub_data, t_map *map, int map_height, int *i)
{
	char	*line;
	int		j;

	j = 0;
	map->width = 0;
	map->height = 0;
	map->gamemap = malloc(sizeof(char *) * (map_height + 1));
	while (cub_data->map->map_raw_datas[*i])
	{
		line = ft_strtrim(map->map_raw_datas[*i], M_EMPTY);
		if (line[0] == '\0' && map->height < map_height)
		{
			free(line);
			return (false);
		}
		else if (line[0] == '\0')
		{
			free(line);
			(*i)++;
			continue ;
		}
		free(line);
		line = ft_strtrim(map->map_raw_datas[*i], "\n");
		if (ft_strlen(line) > (size_t)map->width)
			map->width = ft_strlen(line);
		map->gamemap[j] = ft_strdup(line);
		(*i)++;
		j++;
		free(line);
		map->height++;
	}
	map->gamemap[j] = NULL;
	return (true);
}
