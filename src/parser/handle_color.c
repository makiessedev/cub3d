/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:53:28 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 00:43:40 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static char	*process_color_line(char **chuncks);
static bool	validate_and_set_colors(t_cub *cub, char *color, char **colors_ref,
				char *to_free);
static bool	parse_color_values(char *colors_raw, char **colors_ref);

void	handle_color(t_cub *cub, char **chuncks, char **colors_ref,
		char *to_free)
{
	int		elements_len;
	char	*color;

	elements_len = ft_count_matrix(chuncks);
	if (elements_len < 2 || elements_len > 6)
	{
		free(to_free);
		ft_free_matrix(chuncks);
		print_error_and_exit(cub, "Invalid arguments of colors");
	}
	color = process_color_line(chuncks);
	if (validate_and_set_colors(cub, color, colors_ref, to_free) == false)
	{
		free(color);
		free(to_free);
		ft_free_matrix(chuncks);
		print_error_and_exit(cub, "Invalid digit color");
	}
	free(color);
}

static char	*process_color_line(char **chuncks)
{
	char		*color;
	char		*temp;
	const char	*empty = "\t ";
	int			i;

	color = ft_strdup(chuncks[1]);
	i = 2;
	while (chuncks[i])
	{
		temp = ft_strdup(color);
		free(color);
		color = ft_strjoin(temp, chuncks[i]);
		free(temp);
		i++;
	}
	temp = ft_strdup(color);
	free(color);
	color = ft_remove_chars(temp, empty);
	free(temp);
	return (color);
}

static bool	validate_and_set_colors(t_cub *cub, char *color, char **colors_ref,
		char *to_free)
{
	if (parse_color_values(color, colors_ref) == false)
	{
		free(color);
		free(to_free);
		print_error_and_exit(cub, "Invalid digit color");
		return (false);
	}
	return (true);
}

static bool	parse_color_values(char *colors_raw, char **colors_ref)
{
	char	**colors;
	int		i;
	int		j;
	int		digit;

	colors = ft_split(colors_raw, ',');
	if (ft_count_matrix(colors) != 3)
		return (ft_free_matrix(colors), false);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (colors[i][j])
		{
			if (!ft_isdigit(colors[i][j]))
				return (ft_free_matrix(colors), false);
			j++;
		}
		digit = ft_atoi(colors[i]);
		if (digit < 0 || digit > 255 || colors_ref[i])
			return (ft_free_matrix(colors), false);
		colors_ref[i] = ft_strdup(colors[i]);
		i++;
	}
	return (ft_free_matrix(colors), true);
}
