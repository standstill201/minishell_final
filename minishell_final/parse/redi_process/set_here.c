/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_here.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:10:08 by codespace         #+#    #+#             */
/*   Updated: 2023/02/23 06:44:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_here_word(t_list *temp)
{
	char	*limiter;

	while (temp && temp->is_meta == 0)
	{
		temp->is_single_quote = 1;
		temp->is_here_word = 1;
		limiter = ft_strjoin(temp->content, "\n");
		free(temp->content);
		temp->content = limiter;
		if (temp)
			temp = temp->next;
	}
}

int	set_here(t_list **parse_separate, int *status)
{
	t_list	*temp;

	temp = *parse_separate;
	while (temp)
	{
		temp = temp->next;
		if (temp && temp->is_meta && ft_strncmp(temp->content, "<<", 2) == 0)
		{
			temp = temp->next;
			while (temp && temp->is_meta && ft_iswhite(temp->content[0]))
				temp = temp->next;
			if (temp && temp->is_meta && !ft_iswhite(temp->content[0]))
				return (unexpected_token_error(temp->content, status));
			handle_here_word(temp);
		}
	}
	return (0);
}
