/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:54:43 by dvargas           #+#    #+#             */
/*   Updated: 2023/01/28 13:22:29 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_mini.h"
#include "libft/libft.h"

int	ft_heredoc_open(t_shell *blk, char *str)
{
	ft_heredoc(blk, str);
	blk->fd_in = open(blk->tmpdoc, O_RDONLY);
	if (blk->fd_in < 0)
	{
		perror("ERNANI");
		return (0);
	}
	close(0);
	dup2(blk->fd_in, 0);
	return (1);
}

int	ft_infile_open(t_shell *blk, char *str)
{
	blk->fd_in = open(str, O_RDONLY);
	if (blk->fd_in < 0)
	{
		perror("ERNANI");
		return (0);
	}
	close(0);
	dup2(blk->fd_in, 0);
	return (1);
}

int	ft_outfile_open(char *str, int flag, t_shell *blk)
{
	char	*outfile_name;
	int		i;

	i = 0;
	while (str[i] != ' ' && str[i])
		i++;
	outfile_name = ft_substr(str, 0, i);
	if (flag == 1)
		blk->fd_in = open(outfile_name, O_APPEND | O_CREAT | O_WRONLY, 0777);
	else
		blk->fd_in = open(outfile_name, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	free(outfile_name);
	dup2(blk->fd_in, 1);
	return (1);
}

int	ft_split_inf(t_shell *blk, char **tmp, int j)
{
	char	**aux;
	int		out;

	aux = ft_split(tmp [j + 1], ' ');
	out = ft_infile_open(blk, aux[0]);
	ft_freeing(aux);
	return (out);
}

int	ft_split_hdoc(t_shell *blk, char **tmp, int j)
{
	char	**aux;
	int		out;

	aux = ft_split(tmp [j + 1], ' ');
	out = ft_heredoc_open(blk, aux[0]);
	ft_freeing(aux);
	return (out);
}

int	ft_redirect_do(t_shell *blk, char **tmp, char *basestring, int j)
{
	int		i;
	int		out;

	i = -1;
	while (basestring[++i])
	{
		if (basestring[i] == SHIFT_R)
			out = ft_outfile_open(tmp[j + 1], 42, blk);
		if (basestring[i] == SHIFT_L)
			out = ft_split_inf(blk, tmp, j);
		if (basestring[i] == SHIFT_DR)
			out = ft_outfile_open(tmp[j + 1], 1, blk);
		if (basestring[i] == SHIFT_DL)
			out = ft_split_hdoc(blk, tmp, j);
		if (!basestring[i + 1])
			close(blk->fd_in);
		j++;
	}
	return (out);
}

void	ft_redirect_access(t_shell *blk, t_input *inp, char **redir)
{
	char	**tmp;

	if (redir == NULL)
		ft_access(blk, inp);
	tmp = inp->args;
	inp->args = redir;
	ft_access(blk, inp);
	inp->args = tmp;
}

void	ft_simple_redirect(t_shell *blk, t_input *inp, char **splited)
{
	char	**tmp;
	char	*basestring;
	int		flag;

	basestring = ft_red_stk(blk->buf);
	tmp = ft_compose_cmd(splited);
	flag = ft_redirect_do(blk, splited, basestring, 0);
	ft_freeing(splited);
	if (tmp[0] && flag)
		ft_redirect_access(blk, inp, tmp);
	ft_restore_fds(blk);
	ft_freeing(tmp);
	free(basestring);
	unlink(blk->tmpdoc);
}
