/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_meta2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 07:31:30 by codespace         #+#    #+#             */
/*   Updated: 2023/02/23 09:33:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_variable_name(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_valid_variable_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	process_dollar(char *return_val, int *index, t_list **root, int *status)
{
	int		index_before;
	char	*var_name;

	index_before = *index;
	(*index)++;
	if (return_val[*index] == '$')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token \'$\'\n", 2);
		*status = 1;
		return (1);
	}
	if (is_valid_variable_name(return_val[*index]))
	{
		while (is_valid_variable_char(return_val[*index]))
			(*index)++;
		var_name = ft_substr(return_val, index_before, *index - index_before);
		ft_lstadd_back(root, ft_lstnew(var_name, 0));
	}
	else
	{
		ft_lstadd_back(root, ft_lstnew(ft_substr(return_val, *index, 2), 0));
		ft_lstlast(*root)->is_single_quote = 1;
		(*index) += 2;
	}
	return (0);
}

void	process_plain_text(char *return_val, int *index, t_list **root)
{
	int		index_before;
	char	*text;

	index_before = *index;
	while (return_val[*index] && return_val[*index] != '$')
		(*index)++;
	text = ft_substr(return_val, index_before, *index - index_before);
	ft_lstadd_back(root, ft_lstnew(text, 0));
}

int	double_quote_task(char *return_val, t_list **root, int *status)
{
	int	index;

	index = 0;
	if (!return_val[0])
	{
		ft_lstadd_back(root, ft_lstnew(ft_strdup(""), 0));
		return (0);
	}
	while (return_val[index])
	{
		if (return_val[index] == '$')
		{
			if (process_dollar(return_val, &index, root, status))
				return (1);
		}
		else
			process_plain_text(return_val, &index, root);
	}
	return (0);
}
