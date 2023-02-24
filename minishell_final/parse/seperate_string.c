/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperate_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:38:45 by codespace         #+#    #+#             */
/*   Updated: 2023/02/23 06:34:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*read_string_before_white_quote(char *str, t_list **root)
{
	int		index;
	char	*return_val;

	index = 0;
	while (str[index] && !is_meta(str[index]))
		index++;
	return_val = ft_substr(str, 0, index);
	ft_lstadd_back(root, ft_lstnew(return_val, 0));
	return (str + index);
}

int	handle_first_pipe(t_list **root, int *status)
{
	t_list	*tmp;

	tmp = (*root)->next;
	while (tmp && tmp->is_meta && tmp->content[0] != '|')
	{
		if (!tmp->is_meta)
			return (0);
		tmp = tmp->next;
	}
	if (tmp && tmp->is_meta && tmp->content[0] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		*status = 2;
		return (1);
	}
	return (0);
}

t_list	*seperate_string(char *str, int *status)
{
	t_list	*root;

	root = ft_lstnew(ft_strdup("root node start"), 0);
	while (*str && ft_iswhite(*str))
		str++;
	while (*str)
	{
		if (is_meta(*str))
			str = parse_meta(str, &root, status);
		else
			str = read_string_before_white_quote(str, &root);
		if (!str)
			return (0);
	}
	if (handle_first_pipe(&root, status))
		return (0);
	return (root);
}
