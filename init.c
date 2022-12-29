/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 07:17:44 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/29 08:13:40 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_mini.h"

//Inicializacao de BLK 
//
t_shell *ft_blkinit(void)
{
	t_shell *blk;

	blk = malloc(sizeof(t_shell));
	blk->cmd = NULL;
	blk->buf = NULL;
	blk->envp = NULL;
	blk->tmpdoc = "conchinha";
	return(blk);
}
