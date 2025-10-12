/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:53:28 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/12 22:57:06 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static bool	set_colors(char *colors_raw, char **colors_ref);

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
		if (set_colors(color, colors_ref) == false)
		{
			free(color);
			free(to_free);
			ft_free_matrix(chuncks);
			print_error_and_exit(cub, "Invalid digit color");
		}
		free(color);
	}
	else
	{
		free(to_free);
		ft_free_matrix(chuncks);
		print_error_and_exit(cub, "Invalid arguments of colors");
	}
}

static bool	set_colors(char *colors_raw, char **colors_ref)
{
	int		i;
	int		j;
	char	**colors;
	int		digit;

	i = 0;
	colors = ft_split(colors_raw, ',');
	if (ft_count_matrix(colors) != 3)
		return (ft_free_matrix(colors), false);
	while (i < 3)
	{
		j = 0;
		while (j < (int)ft_strlen(colors[i]))
		{
			if (ft_isprint(colors[i][j]))
			{
				if (!ft_isdigit(colors[i][j]))
					return (ft_free_matrix(colors), false);
			}
			j++;
		}
		digit = ft_atoi(colors[i]);
		if (digit > 255 || digit < 0)
			return (ft_free_matrix(colors), false);
		if (colors_ref[i])
			return (ft_free_matrix(colors), false);
		colors_ref[i] = ft_strdup(colors[i]);
		i++;
	}
	ft_free_matrix(colors);
	return true;
}
