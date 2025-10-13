/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 05:18:15 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 05:18:19 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_matrix(char **mat)
{
	int	count;

	count = 0;
	while (mat[count])
		count++;
	return (count);
}
