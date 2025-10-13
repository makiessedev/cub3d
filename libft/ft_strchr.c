/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 09:09:20 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 05:17:21 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int i)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (unsigned char)i)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)i)
		return ((char *)s);
	return (0);
}
