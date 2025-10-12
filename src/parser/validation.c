/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:03:18 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/12 18:41:35 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static bool	validate_first_and_last_line(t_map *map);
static bool	validate_lines(t_map *map);
static void	validate_and_get_player_position(t_cub *cub);

void	validate_map(t_cub *cub)
{
	if (validate_first_and_last_line(cub->map) == false)
		print_error_and_exit(cub, "Invalid map");
	pad_map_lines(cub->map->gamemap, cub->map->width);
	if (validate_lines(cub->map) == false)
		print_error_and_exit(cub, "Invalid map");
	validate_and_get_player_position(cub);
}

static bool	validate_first_and_last_line(t_map *map)
{
	char	*first_line;
	char	*last_line;
	int		i;

	first_line = map->gamemap[0];
	last_line = map->gamemap[map->height - 1];
	i = 0;
	while (first_line[i] != '\0')
	{
		if (first_line[i] != ' ' && first_line[i] != '1')
			return (false);
		i++;
	}
	i = 0;
	while (last_line[i] != '\0')
	{
		if (last_line[i] != ' ' && last_line[i] != '1')
			return (false);
		i++;
	}
	return (true);
}

static bool	validate_lines(t_map *map)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map->gamemap[i] != NULL)
	{
		line = ft_strtrim(map->gamemap[i], M_EMPTY);
		if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
		{
			free(line);
			return (false);
		}
		free(line);
		j = 0;
		if (validate_lines_aux(map, &i, &j) == false)
			return (false);
		i++;
	}
	return (true);
}

static void	validate_and_get_player_position(t_cub *cub)
{
	int		y;
	int		x;
	char	**lines;
	char	*line;

	y = 0;
	x = 0;
	lines = cub->map->gamemap;
	while (lines[y] != NULL)
	{
		line = ft_strdup(lines[y]);
		x = 0;
		while (line[x] != '\0')
		{
			if (line[x] == 'N' || line[x] == 'S' || line[x] == 'E'
				|| line[x] == 'W')
			{
				if (cub->player->pos.x)
				{
					free(line);
					print_error_and_exit(cub, "Duplated player");
				}
				cub->player->pos.x = x + 0.5;
				cub->player->pos.y = y + 0.5;
				cub->map->gamemap[y][x] = '0';
			}
			x++;
		}
		free(line);
		y++;
	}
	if (!cub->player->pos.x)
		print_error_and_exit(cub, "Player not seted");
}
