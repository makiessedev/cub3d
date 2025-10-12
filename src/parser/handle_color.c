/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:53:28 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/12 05:31:55 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static void	set_colors(t_cub *cub, char *colors_raw, char **colors_ref,
				char *to_free, char **to_free2);

void	handle_color(t_cub *cub, char **chuncks, char **colors_ref,
		char *to_free)
{
	int			elements_len;
	const char	*EMPTY = "\t ";
	char		*color;
	char		*temp;
	int			i;

	elements_len = ft_count_matrix(chuncks);
	if (elements_len >= 2 && elements_len <= 6)
	{
		color = ft_strdup(chuncks[1]);
		if (elements_len > 2)
		{
			i = 2;
			while (chuncks[i])
			{
				temp = ft_strdup(color);
				free(color);
				color = ft_strjoin(temp, chuncks[i]);
				free(temp);
				i++;
			}
			temp = strdup(color);
			free(color);
			color = ft_remove_chars(temp, EMPTY);
			free(temp);
		}
		set_colors(cub, color, colors_ref, to_free, chuncks);
		free(color);
	}
	else
	{
		free(to_free);
		ft_free_matrix(chuncks);
		print_error_and_exit(cub, "Invalid arguments of colors");
	}
}

static void	set_colors(t_cub *cub, char *colors_raw, char **colors_ref,
		char *to_free, char **to_free2)
{
	int		i;
	int		j;
	char	**colors;
	int		digit;

	i = 0;
	colors = ft_split(colors_raw, ',');
	if (ft_count_matrix(colors) != 3)
	{
		free(colors_raw);
		free(to_free);
		ft_free_matrix(colors);
		ft_free_matrix(to_free2);
		print_error_and_exit(cub, "Invalid color RGB");
	}
	while (i < 3)
	{
		j = 0;
		while (j < (int)ft_strlen(colors[i]))
		{
			if (ft_isprint(colors[i][j]))
			{
				if (!ft_isdigit(colors[i][j]))
				{
					free(colors_raw);
					free(to_free);
					ft_free_matrix(colors);
					ft_free_matrix(to_free2);
					print_error_and_exit(cub, "Invalid digit color");
				}
			}
			j++;
		}
		digit = ft_atoi(colors[i]);
		if (digit > 255 || digit < 0)
		{
			free(colors_raw);
			free(to_free);
			ft_free_matrix(colors);
			ft_free_matrix(to_free2);
			print_error_and_exit(cub, "Invalid Color");
		}
		if (colors_ref[i])
		{
			free(colors_raw);
			free(to_free);
			ft_free_matrix(colors);
			ft_free_matrix(to_free2);
			print_error_and_exit(cub, "Invalid color: duplicated value");
		}
		colors_ref[i] = ft_strdup(colors[i]);
		i++;
	}
	ft_free_matrix(colors);
}
