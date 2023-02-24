/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_meta3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 07:13:20 by codespace         #+#    #+#             */
/*   Updated: 2023/02/23 07:22:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_meta(char c)
{
	if (c == '|' || c == '>' || c == '<' || ft_iswhite(c)
		|| c == '\'' || c == '\"' || c == '$' || c == ';' || c == '\\')
		return (1);
	else
		return (0);
}

char	*read_string_before_redirection(char *str, t_list **root)
{
	char	*return_val;

	if (*(str + 1) && *(str + 1) == *(str))
	{
		return_val = (char *)malloc(sizeof(char) * 3);
		return_val[0] = *str;
		return_val[1] = *str;
		return_val[2] = 0;
		ft_lstadd_back(root, ft_lstnew(return_val, 1));
		return (str + 2);
	}
	return_val = (char *)malloc(sizeof(char) * 2);
	return_val[0] = *str;
	return_val[1] = '\0';
	ft_lstadd_back(root, ft_lstnew(return_val, 1));
	return (str + 1);
}

char	*read_string_before_dollar(char *str, t_list **root, int *status)
{
	int		index;
	char	*return_val;

	index = 1;
	if (str[index] == '?')
	{
		ft_lstadd_back(root, ft_lstnew(ft_strdup("?"), 0));
		ft_lstlast(*root)->is_question_dollor = 1;
		return (str + 2);
	}
	if (ft_isalpha(str[index]) || str[index] == '_')
		index++;
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token \'$\'\n", 2);
		*status = 1;
		return (0);
	}
	while (str[index] && (ft_isalnum(str[index]) || str[index] == '_'))
		index++;
	return_val = ft_substr(str, 0, index);
	ft_lstadd_back(root, ft_lstnew(return_val, 0));
	return (str + index);
}
