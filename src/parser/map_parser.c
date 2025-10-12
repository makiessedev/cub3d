/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:01:29 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/12 05:24:41 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static int	count_line(t_map *map);
static void	save_elements(t_cub *cub);
static char	**split_line(t_cub *cub, char *map_line, int *i);

bool	parser_map(t_cub *cub, char *file)
{
	t_map	*map;
	int		fd;
	int		i;
	char	*line;

	map = cub->map;
	map->map_path = file;
	fd = open_file(map->map_path);
	map->map_raw_datas = ft_calloc(count_line(map) + 1, sizeof(char *));
	if (is_file_empty(file))
		print_error_and_exit(cub, "Empty file");
	line = get_next_line(fd);
	i = -1;
	while (line != NULL)
	{
		map->map_raw_datas[++i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	map->map_raw_datas[i + 1] = NULL;
	close(fd);
	save_elements(cub);
	if (!map->gamemap)
		print_error_and_exit(cub, "Invalid Map");
	return (validate_map(cub), true);
}

void	save_map(t_cub *cub, t_map *map, int *i)
{
	int	map_height;

	if (map->NO && map->SO && map->WE && map->EA && map->C[0] && map->F[0])
	{
		map_height = count_map_height(cub, *i);
		if (map_height == 0)
			print_error_and_exit(cub, "Invalid map");
		salt_to_first_linemap(map, i);
		if (get_map(cub, map, map_height, i) == false)
			print_error_and_exit(cub, "Space inside map");
		return ;
	}
}

static void	save_elements(t_cub *cub)
{
	int		i;
	char	**chuncks;
	char	*has_tab;

	i = 0;
	while (cub->map->map_raw_datas[i])
	{
		has_tab = ft_strchr(cub->map->map_raw_datas[i], '\t');
		if (has_tab)
			print_error_and_exit(cub, "tab is not accepted");
		chuncks = split_line(cub, cub->map->map_raw_datas[i], &i);
		if (chuncks == NULL)
		{
			ft_free_matrix(chuncks);
			continue ;
		}
		if (get_color_and_texture(cub, cub->map, chuncks, &i) == false)
		{
			ft_free_matrix(chuncks);
			print_error_and_exit(cub, "Invalid Key: Color or Textures");
		}
		ft_free_matrix(chuncks);
		save_map(cub, cub->map, &i);
		i++;
	}
}

static int	count_line(t_map *map)
{
	char	*line;
	int		count;
	int		fd;

	fd = open_file(map->map_path);
	line = get_next_line(fd);
	count = 0;
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	close(fd);
	return (count);
}

static char	**split_line(t_cub *cub, char *map_line, int *i)
{
	char	**chuncks;
	char	*line;

	line = ft_strtrim(map_line, M_EMPTY);
	if (ft_strlen(line) == 0 || ft_strlen(line) == 1)
	{
		(*i)++;
		free(line);
		return (NULL);
	}
	chuncks = ft_split(line, M_SPACE);
	if (ft_count_matrix(chuncks) == 1)
	{
		ft_free_matrix(chuncks);
		chuncks = ft_split(line, M_TAB);
		if (ft_count_matrix(chuncks) == 1)
		{
			free(line);
			ft_free_matrix(chuncks);
			print_error_and_exit(cub, "invalid color or textures");
		}
	}
	free(line);
	return (chuncks);
}
