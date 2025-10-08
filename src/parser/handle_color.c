/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:53:28 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/08 10:53:29 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static void	set_colors(t_cub *cub, char *colors_raw, char **colors_ref);

void	handle_color(t_cub *cub, char **chuncks, int argc, char **colors_ref)
{
	const char	*EMPTY = "\t ";
	char		*color;
	char		*temp;
	int			i;

	if (argc >= 2 && argc <= 6)
	{
		color = ft_strdup(chuncks[1]);
		if (argc > 2)
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
		set_colors(cub, color, colors_ref);
		free(color);
	}
	else
	{
		printf("arg-> %i", argc);
		print_error_and_exit(cub, "Invalid arguments of colors");
	}
}

static void	set_colors(t_cub *cub, char *colors_raw, char **colors_ref)
{
	int		i;
	int		j;
	char	**colors;
	int		digit;

	i = 0;
	colors = ft_split(colors_raw, ',');
	if (ft_count_matrix(colors) > 3)
	{
		ft_free_matrix(colors);
		print_error_and_exit(cub, "Invalid color many arguments");
	}
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (ft_isprint(colors[i][j]))
			{
				if (!ft_isdigit(colors[i][j]))
				{
					ft_free_matrix(colors);
					print_error_and_exit(cub, "Invalid digit color");
				}
			}
			j++;
		}
		digit = ft_atoi(colors[i]);
		if (digit > 255 || digit < 0)
		{
			ft_free_matrix(colors);
			print_error_and_exit(cub, "Invalid Color");
		}
		if (colors_ref[i])
		{
			ft_free_matrix(colors);
			print_error_and_exit(cub, "Invalid color: duplicated value");
		}
		colors_ref[i] = ft_strdup(colors[i]);
		i++;
	}
	ft_free_matrix(colors);
}
