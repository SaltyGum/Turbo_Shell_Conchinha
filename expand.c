/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas <dvargas@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:23:23 by dvargas           #+#    #+#             */
/*   Updated: 2022/12/30 21:33:13 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_mini.h"
#include "libft/libft.h"

// checa se tem uma quantidade par de aspas
int	ft_double_quote_check(char *str)
{
	int		i;
	int		quotes;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
				quotes++;
		if (str[i] == '"')
				quotes++;
		i++;
	}
	if ((quotes % 2 == 0) && (quotes != 0))
		return (0);
	return (1);
}

// vejo o tamanho da variavel
int	ft_var_size(char *str)
{
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			break ;
		i++;
	}
	while (str[i])
	{
		if (ft_isspace(str[i]) == 1 || str[i] == '"' || str[i] == '\'')
			break ;
		size++;
		i++;
	}
	return (size - 1);
}

//verifico se a variavel e valida? talvez seja util no export
int	ft_var_isvalid(char *str)
{
	int	i;

	i = 1;
	if (ft_isspace(str[i + 1]) == 0)
		return (1);
	if ((str[i + 1] >= '0' && str[i + 1] <= '9') || str[i + 1] == '?')
		return (1);
	return (0);
}

// crio a variavel dando join no =
char	*ft_create_var(char *str)
{
	int		i;
	int		start;
	int		len;
	char	*tmp;
	char	*var;

	start = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			break ;
		i++;
	}
	start = i + 1;
	len = ft_var_size(str);
	var = ft_substr(str, start, len);
	if (!var)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	var = tmp;
	return (var);
}

// busco a variavel na nossa env e retorno o resultado da busca depois do =
char	*ft_var_ret(t_shell *blk, char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = ft_search(blk->envp, str);
	if (!ret)
		return (NULL);
	while (ret[i] != '=')
		i++;
	return (&ret[i+1]);
}

void	ft_update_dquote(int *i, int *flag, char c)
{
	int		mirror_i;
	int		mirror_flag;

	mirror_i = *i;
	mirror_flag = *flag;
	if (c == '"' && mirror_flag == 0)
	{
		mirror_i++;
		mirror_flag++;
	}
	else if (c == '"' && mirror_flag == 1)
	{
		mirror_i++;
		mirror_flag = 0;
	}
	*i = mirror_i;
	*flag = mirror_flag;
}

void	ft_update_squote(int *i, int *flag, char c)
{
	int		mirror_i;
	int		mirror_flag;

	mirror_i = *i;
	mirror_flag = *flag;
	if (c == '\'' && mirror_flag == 0)
	{
		mirror_i++;
		mirror_flag++;
	}
	else if (c == '\'' && mirror_flag == 1)
	{
		mirror_i++;
		mirror_flag = 0;
	}
	*i = mirror_i;
	*flag = mirror_flag;
}

void	ft_expand(t_shell *blk, char *str)
{
	int		i;
	int		flag;
	char	*tmp;

	i = 0;
	flag = 0;
	blk->i = 2;
	while (str[i])
	{
		if (!ft_double_quote_check(str))
		{
			ft_update_dquote(&i, &flag, str[i]);
			ft_update_squote(&i, &flag, str[i]);
		}
		else
			flag = 1;
		if (str[i] == '$' && flag == 1)
		{
			tmp = ft_create_var(&str[i]);
			i += ft_strlen(tmp) - 1;
			printf("%s", ft_var_ret(blk, tmp));
			free(tmp);
		}
		else
			printf("%c", str[i]);
		i++;
	}
}

//Buscar $ na string, checar se ela e valida 
//lemnbrar que nao tem variavel que comece com numero e ?
//identificar o tamanho da variavel
//localizar a variavel em ENV, se for valido utilize ela se nao ignore o comando
//fazer uma substring com a string correta 