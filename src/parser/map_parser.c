/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:01:29 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/10 11:24:02 by mmorais          ###   ########.fr       */
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
	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		map->map_raw_datas[i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	map->map_raw_datas[i] = NULL;
	close(fd);
	save_elements(cub);
	validate_map(cub);
	return (true);
}

static void	save_elements(t_cub *cub)
{
	int		i;
	char	**chuncks;
	t_map	*map;
	int		map_height;
  char *has_tab;

	i = 0;
	map = cub->map;
	while (map->map_raw_datas[i])
	{
    has_tab = ft_strchr(map->map_raw_datas[i], '\t');
    if (has_tab)
      print_error_and_exit(cub, "tab is not accepted");
		chuncks = split_line(cub, map->map_raw_datas[i], &i);
		if (chuncks == NULL)
		{
			ft_free_matrix(chuncks);
			continue ;
		}
		if (get_color_and_texture(cub, map, chuncks, &i) == false)
		{
			ft_free_matrix(chuncks);
			print_error_and_exit(cub, "Invalid Key: Color or Textures");
		}
		ft_free_matrix(chuncks);
		if (map->NO && map->SO && map->WE && map->EA && map->C[0] && map->F[0])
		{
			map_height = count_map_height(cub, i);
			salt_to_first_linemap(map, &i);
			if (get_map(cub, map, map_height, &i) == false)
				print_error_and_exit(cub, "Error\nSpace inside map");
			return ;
		}
		i++;
	}
}

static int	count_line(t_map *map)
{
	char	*line;
	int		count;
	int		fd;

	fd = open_file(map->map_path);
	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
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
