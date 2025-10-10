/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_and_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:04:05 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/10 17:16:04 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	print_error_and_exit(t_cub *cub, char *msg)
{
	(void)cub;
	char *fullMessage;

	fullMessage = ft_strjoin("Error\n", msg);
	ft_putendl_fd(fullMessage, 2);
	free(fullMessage);
	exit(0);
}
