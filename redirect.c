/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:54:43 by dvargas           #+#    #+#             */
/*   Updated: 2023/01/25 09:14:15 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_mini.h"
#include "libft/libft.h"

//Tomar cuidado com o isalpha, pode bugar algumas coisas no futuro uma solucao
//para um possivel problema com variavel seja ignorar o $ como faco com o space
int	ft_symbol_control(int *i, char *str, char good)
{
	if (str[*i + 1] == good)
		*i = *i + 1;
	while (str[*i])
	{
		*i = *i + 1;
		if (ft_isalpha(str[*i]) == 1 && str[*i] != ' ')
			return (0);
		if (str[*i] == '<' || str[*i] == '>' || str[*i] == '\0')
			return (-1);
	}
	return (0);
}

int	ft_count_symbols(char *str)
{
	int		i;
	int		count;
	int		quote;

	quote = 0;
	i = -1;
	count = 0;
	while (str[++i])
	{
		ft_update_quote(&quote, str[i]);
		if (str[i] == '>' && quote == 0)
		{
			count++;
			if (ft_symbol_control(&i, str, '>') == -1)
				return (-1);
		}
		else if (str[i] == '<' && quote == 0)
		{
			count++;
			if (ft_symbol_control(&i, str, '<') == -1)
				return (-1);
		}
	}
	return (count);
}

char	**ft_split_in_redirect(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**ret;

	i = 0;
	j = 0;
	k = 0;
	ret = ft_calloc(sizeof(char *), ft_count_redir_sep(str) + 2);
	if (!ret)
		return (printf("MALLOC CRASH"), NULL);
	while (str[i])
	{
		if (ft_is_redir_sep(str, i))
		{
			ret[j] = ft_substr(str, k, i - k);
			k = ft_i_next_redir(&str[i]) + i;
			i = k;
			j++;
		}
		i++;
	}
	ret[j] = ft_substr(str, k, i - k);
	ret[j + 1] = NULL;
	return (ret);
}

void	ft_heredoc_open(t_shell *blk, char *str)
{
	ft_heredoc(blk, str);
	blk->fd_in = open(blk->tmpdoc, O_RDONLY);
	if (blk->fd_in < 0)
		perror("ERNANI");
	close(0);
	dup2(blk->fd_in, 0);
}

void	ft_infile_open(t_shell *blk, char *str)
{
	blk->fd_in = open(str, O_RDONLY);
	if (blk->fd_in < 0)
		perror("ERNANI");
	close(0);
	dup2(blk->fd_in, 0);
}

void	ft_outfile_open(char *str, int flag)
{
	int		outfile;
	char	*outfile_name;
	int		i;

	i = 0;
	while (str[i] != ' ')
		i++;

	outfile_name = ft_substr(str, 0, i);
	if (flag == 1)
		outfile = open(outfile_name, O_APPEND | O_CREAT | O_WRONLY, 0777);
	else
		outfile = open(outfile_name, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	dup2(outfile, 1);
}

char  *ft_redirect_clean(char *str)
{
	int		i;

	i = 0;
	while(str[i] != ' ')
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
	}
	return(&str[i + 1]);
}

char  **ft_compose_cmd(char **matrix)
{
	char  *tmp;
	char  **aux;
	int   i;
	int   j;

	i = 1;
	tmp = matrix[0];
	while (matrix[i])
	{
		j = 1;
		aux = ft_split(matrix[i], ' ');
		while (aux[j])
		{
			ft_swapjoin(&tmp, aux[j]);
			ft_swapjoin(&tmp, " ");
			j++;
		}
		ft_freeing(aux);
		i++;
	}
	aux = ft_split(tmp, ' ');
	free(tmp);
	return (aux);
}

void	ft_simple_redirect(t_shell *blk, t_input *inp)
{
	char	*basestring;
	int		i;
	int		j;
	char	**tmp;
	char  **aux;

	tmp = inp->args;
	inp->args = ft_compose_cmd(tmp);
	i = 0;
	while (inp->args[i])
	{
		printf("-%s-\n", inp->args[i]);
		i++;
	}
	j = 0;
	i = 0;
	basestring = ft_red_stk(blk->buf);
	while(basestring[i])
	{
		if(basestring[i] == SHIFT_R)
		{
			ft_outfile_open(tmp[j + 1], 42);
		}
		if(basestring[i] == SHIFT_L)
		{
			aux = ft_split(tmp [j + 1], ' ');
			ft_infile_open(blk, aux[0]);
			ft_freeing(aux);
		}
		if(basestring[i] == SHIFT_DR)
			ft_outfile_open(tmp[j + 1], 1);
		if(basestring[i] == SHIFT_DL)
		{
			aux = ft_split(tmp[j + 1], ' ');
			ft_heredoc_open(blk, aux[0]);
			ft_freeing(aux);
		}
		i++;
		j++;
	}
	if (inp->args[0])
	{
		ft_access(blk, inp);
	}
	ft_restore_fds(blk);
	free(basestring);
	unlink(blk->tmpdoc);
	//ft_freeing(tmp);
}
