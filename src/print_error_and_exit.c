/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_and_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:04:05 by mmorais           #+#    #+#             */
/*   Updated: 2025/10/08 11:04:07 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	print_error_and_exit(t_cub *cub, char *msg)
{
	(void)cub;
	ft_putendl_fd(msg, 2);
	exit(0);
}
