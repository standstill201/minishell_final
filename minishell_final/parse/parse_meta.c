/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 07:28:27 by codespace         #+#    #+#             */
/*   Updated: 2023/02/23 07:22:25 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*extract_string(char *str, char trg)
{
	int		index;

	index = 0;
	while (str[index])
	{
		if (str[index] == trg)
			return (ft_substr(str, 0, index));
		index++;
	}
	if (str[index] == '\0')
		unexpected_token_end(0);
	return (NULL);
}

char	*read_string_before_quote(char *str, t_list **root, int *status)
{
	char	*return_val;
	char	trg;

	trg = *str;
	str++;
	return_val = extract_string(str, trg);
	if (trg == '\"')
	{
		if (double_quote_task(return_val, root, status))
			return (NULL);
	}
	else
	{
		ft_lstadd_back(root, ft_lstnew(return_val, 0));
		ft_lstlast(*root)->is_single_quote = 1;
	}
	return (str + ft_strlen(return_val) + 1);
}

char	*read_string_while_white(char *str, t_list **root)
{
	int		index;
	char	*return_val;

	index = 0;
	while (str[index] && ft_iswhite(str[index]))
		index++;
	return_val = ft_substr(str, 0, index);
	ft_lstadd_back(root, ft_lstnew(return_val, 1));
	return (str + index);
}

char	*read_string_before_pipe(char *str, t_list **root, int *status)
{
	int		index;
	char	*return_val;

	index = 0;
	str++;
	if (*str == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|\'\n", 2);
		*status = 2;
		return (0);
	}
	return_val = (char *)malloc(sizeof(char) * 2);
	return_val[0] = '|';
	return_val[1] = '\0';
	ft_lstadd_back(root, ft_lstnew(return_val, 1));
	return (str);
}

char	*parse_meta(char *str, t_list **root, int *status)
{
	char	*return_val;

	if (*str == '\'' || *str == '\"')
		return_val = read_string_before_quote(str, root, status);
	else if (*str == '|')
		return_val = read_string_before_pipe(str, root, status);
	else if (*str == '>' || *str == '<')
		return_val = read_string_before_redirection(str, root);
	else if (ft_iswhite(*str))
		return_val = read_string_while_white(str, root);
	else if (*str == '$')
		return_val = read_string_before_dollar(str, root, status);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(*str, 2);
		ft_putstr_fd("\'\n", 2);
		*status = 2;
		return (0);
	}
	return (return_val);
}
