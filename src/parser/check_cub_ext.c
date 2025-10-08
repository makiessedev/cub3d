/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_ext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:50:52 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/08 19:01:30 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int	check_cub_extension(const char *f)
{
	int	len;

	if (!f)
		return (0);
	len = ft_strlen(f);
	if (len < 5)
		return (0);
	if (f[len - 4] == '.')
	{
		if (f[len - 3] == 'c' && f[len - 2] == 'u' && f[len - 1] == 'b')
			return (1);
	}
	return (0);
}
