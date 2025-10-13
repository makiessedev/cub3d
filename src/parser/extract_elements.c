/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:53:14 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/14 00:11:57 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static void	get_map2(t_map *map, char *line, int *i, int *j);

static bool	handle_map_element(t_cub *cub_data, t_map *map, char **elements,
		char *key)
{
	if (!ft_strncmp(key, M_NO, ft_strlen(key)))
		handle_texture(cub_data, elements, &(map->no), key);
	else if (!ft_strncmp(key, M_SO, ft_strlen(key)))
		handle_texture(cub_data, elements, &(map->so), key);
	else if (!ft_strncmp(key, M_WE, ft_strlen(key)))
		handle_texture(cub_data, elements, &(map->we), key);
	else if (!ft_strncmp(key, M_EA, ft_strlen(key)))
		handle_texture(cub_data, elements, &(map->ea), key);
	else if (!ft_strncmp(key, M_FLOOR, ft_strlen(key)))
		handle_color(cub_data, elements, map->f, key);
	else if (!ft_strncmp(key, M_CEIL, ft_strlen(key)))
		handle_color(cub_data, elements, map->c, key);
	else
		return (false);
	return (true);
}

bool	get_color_and_texture(t_cub *cub_data, t_map *map, char **elements,
		int *i)
{
	char	*key;
	bool	success;

	key = ft_strtrim(elements[0], M_EMPTY);
	success = handle_map_element(cub_data, map, elements, key);
	if (!success)
		return (free(key), false);
	free(key);
	if (map->no && map->so && map->we && map->ea && map->c[0] && map->f[0])
		(*i)++;
	return (true);
}

static bool	process_map_line(t_map *map, int *i, int *j, int hight)
{
	char	*line;

	line = ft_strtrim(map->map_raw_datas[*i], M_EMPTY);
	if (!line)
		return (false);
	if (line[0] == '\0' && map->height < hight)
		return (free(line), false);
	else if (line[0] == '\0')
	{
		free(line);
		(*i)++;
		return (true);
	}
	free(line);
	line = ft_strtrim(map->map_raw_datas[*i], "\n");
	if (ft_strlen(line) > (size_t)map->width)
		map->width = ft_strlen(line);
	get_map2(map, line, i, j);
	return (true);
}

bool	get_map(t_cub *cub_data, t_map *map, int map_height, int *i)
{
	int		j;

	j = 0;
	map->gamemap = malloc(sizeof(char *) * (map_height + 1));
	if (!map->gamemap)
		return (false);
	while (cub_data->map->map_raw_datas[*i])
	{
		if (!process_map_line(map, i, &j, map_height))
			return (false);
	}
	map->gamemap[j] = NULL;
	return (true);
}

static void	get_map2(t_map *map, char *line, int *i, int *j)
{
	map->gamemap[*j] = ft_strdup(line);
	(*i)++;
	(*j)++;
	free(line);
	map->height++;
}
