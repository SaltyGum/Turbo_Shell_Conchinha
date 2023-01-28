/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:23:23 by dvargas           #+#    #+#             */
/*   Updated: 2023/01/28 11:11:33 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_mini.h"
#include "libft/libft.h"

// crio a variavel dando join no =
char	*ft_create_var(char *str, int i, int start, char *tmp)
{
	int		len;
	char	*var;

	while (str[i])
	{
		if (str[i] == '$')
			break ;
		i++;
	}
	start = i + 1;
	len = ft_var_size(str);
	var = ft_substr(str, start, len); // malloc
	if (!var)
		return (NULL);
	i = 1;
	if (!ft_var_isvalid(var))
	{
		while (ft_isalnum(var[i]) || var[i] == '_')
			i++;
		tmp = ft_substr(var, 0, i);
		free(var);
	}
	var = ft_strjoin(tmp, "=");
	free(tmp);
	return (var);
}

// busco a variavel na nossa env e retorno o resultado da busca depois do =
char	*ft_var_ret(t_shell *blk, char *str)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	tmp = ft_search(blk->envp, str);
	if (tmp == NULL)
		return (NULL);
	while (tmp[i] != '=')
		i++;
	ret = ft_strdup(&tmp[i + 1]);
	free(tmp);
	return (ret);
}
void	ft_expand_return(int *i, char *end, char **ret)
{
	*i = *i + 1;
	end = ft_itoa(g_return);
	if(end != NULL)
	{
		ft_swapjoin(ret, end);
		free(end);
	}
}

void ft_expand_var(char *end, char **ret)
{
	if (end != NULL)
	{
		ft_swapjoin(ret, end);
		free(end);
	}
}

// O -1 e importante pq ele faz a len com o = mas imprime sem ele, logo o
// caractere depois de variavel esta sendo ignorado, com o -1 retornamos correto
char	*ft_chase(t_shell *blk, char *str, int i, int flag)
{
	char	*tmp;
	char	*ret;
	char	*end;

	ret = ft_calloc(1, 1);
	while (str[++i])
	{
		if (ft_update_quote(&flag, str[i]) == 1)
			continue ;
		else if (str[i] == '$' && str[i + 1] == '?')
			ft_expand_return(&i, end, &ret);
		else if ((str[i] == '$')
			&& (flag != 1) && (!ft_var_isvalid(&str[i + 1])))
		{
			tmp = ft_create_var(&str[i], 0, 0, NULL);
			i += ft_strlen(tmp) - 1;
			end = ft_var_ret(blk, tmp);
			ft_expand_var(end, &ret);
			free(tmp);
		}
		else
			ft_swapjoinchar(&ret, str[i]);
	}
	return (ret);
}

char	*ft_expand(t_shell *blk, char *str)
{
	char	*tmp;

	tmp = ft_chase(blk, str, -1, 0);
	free(str);
	return (tmp);
}
