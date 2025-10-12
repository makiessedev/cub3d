/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:01:41 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/11 12:02:29 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static char	*ft_remove_chars2(const char *s, const char *set, char *dest,
				size_t set_len);

char	*ft_remove_chars(const char *s, const char *set)
{
	char	*new_s;

	size_t s_len, set_len;
	if (!s || !set)
		return (NULL);
	s_len = strlen(s);
	set_len = strlen(set);
	new_s = (char *)malloc(s_len + 1);
	if (!new_s)
		return (NULL);
	new_s = ft_remove_chars2(s, set, new_s, set_len);
	return (new_s);
}

static char	*ft_remove_chars2(const char *s, const char *set, char *dest,
		size_t set_len)
{
	int	char_is_in_set;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		char_is_in_set = 0;
		for (size_t k = 0; k < set_len; k++)
		{
			if (s[i] == set[k])
			{
				char_is_in_set = 1;
				break ;
			}
		}
		if (!char_is_in_set)
		{
			dest[j] = s[i];
			j++;
		}
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\n On open map");
		exit(0);
	}
	return (fd);
}

void	pad_map_lines(char **map, int max_len)
{
	int		y;
	int		len;
	char	*new_line;

	y = 0;
	while (map[y])
	{
		len = ft_strlen(map[y]);
		if (len < max_len)
		{
			new_line = malloc(max_len + 1);
			ft_memcpy(new_line, map[y], len);
			ft_memset(new_line + len, ' ', max_len - len);
			new_line[max_len] = '\0';
			free(map[y]);
			map[y] = new_line;
		}
		y++;
	}
}
