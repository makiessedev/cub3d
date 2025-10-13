/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 05:17:37 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/13 05:17:42 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_matrix(char **mat)
{
	int	i;

	if (mat == NULL)
	{
		return ;
	}
	i = 0;
	while (mat[i] != NULL)
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}
