/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 07:17:44 by dvargas           #+#    #+#             */
/*   Updated: 2023/01/25 10:27:28 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_mini.h"

//Inicializacao do MINISHELL

t_shell	*ft_blk_init(void)
{
	t_shell	*blk;

	blk = ft_calloc(sizeof(t_shell), 1);
	blk->cmd = NULL;
	blk->buf = NULL;
	blk->envp = NULL;
	blk->tmpdoc = ".TEMPFILEHEREDOC";
	blk->heredoc_name = NULL;
	blk->rs = 0;
	blk->infilename = NULL;
	blk->outfile_name = NULL;
	blk->tmp = NULL;
	blk->aux = NULL;
	blk->append = 0;
	blk->stdin_backup = dup(0);
	blk->stdout_backup = dup(1);
	return (blk);
}

t_input	*ft_input_init(void)
{
	t_input	*inp;

	inp = ft_calloc(sizeof(t_input), 1);
	inp->cmd = NULL;
	inp->args = NULL;
	inp->tmp = NULL;
	inp->echo_print = NULL;
	inp->new_path = NULL;
	inp->ex_name = NULL;
	inp->ex_val = NULL;
	inp->un_name = NULL;
	inp->exit_error = 0;
	inp->size = 0;
	return (inp);
}
