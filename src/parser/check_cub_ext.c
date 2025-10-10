/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_ext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:50:52 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/10 16:36:35 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

bool	check_cub_extension(const char *f)
{
  int	len;

	if (!f)
  return (false);
	len = ft_strlen(f);
	if (len < 6)
  return (false);
  if (f[len - 5] == '/')
    return (false);
	if (f[len - 4] == '.')
	{
    if (f[len - 3] == 'c' && f[len - 2] == 'u' && f[len - 1] == 'b')
      return (true);
	}
	return (false);
}
