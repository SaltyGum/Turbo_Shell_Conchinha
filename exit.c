/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeluiz4 <jeffluiz97@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 08:24:41 by jeluiz4           #+#    #+#             */
/*   Updated: 2022/12/29 08:27:20 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_mini.h"

void	ft_exit(char *str)
{
	if (!ft_strncmp(str, "exit", 4) || str == NULL)
	{
		free(str);
		write(1, "exit\n", 5);
		exit(0);
	}
}
