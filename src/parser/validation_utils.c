/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:02:13 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/11 12:02:34 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

bool	validate_lines2(t_map *map, int i, int j)
{
	if (i + 1 < map->height)
	{
		if (map->gamemap[i + 1][j] && map->gamemap[i + 1][j] != ' '
			&& map->gamemap[i + 1][j] != '1')
			return (false);
	}
	if (i - 1 > 0)
	{
		if (map->gamemap[i - 1] && map->gamemap[i - 1][j] && map->gamemap[i
			- 1][j] != ' ' && map->gamemap[i - 1][j] != '1')
			return (false);
	}
	if (j + 1 < map->width)
	{
		if (map->gamemap[i][j + 1] && map->gamemap[i][j + 1] != ' '
			&& map->gamemap[i][j + 1] != '1')
			return (false);
	}
	if (j - 1 > 0)
	{
		if (map->gamemap[i][j - 1] && map->gamemap[i][j - 1] != ' '
			&& map->gamemap[i][j - 1] != '1')
			return (false);
	}
	return (true);
}

int	is_file_empty(char *path)
{
	int		fd;
	char	*line;
	int		has_content;
	char	*trimmend;

	fd = open_file(path);
	line = get_next_line(fd);
	has_content = 0;
	while (line != NULL)
	{
		trimmend = ft_strtrim(line, " \t\n");
		if (line[0] != '\0' && trimmend[0] != '\0')
			has_content = 1;
		free(line);
		free(trimmend);
		line = get_next_line(fd);
	}
	close(fd);
	return (!has_content);
}
