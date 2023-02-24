/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 07:30:16 by codespace         #+#    #+#             */
/*   Updated: 2023/02/23 07:30:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_pipe_n(t_list **root)
{
	t_list	*temp;
	int		pipe_n;

	temp = *root;
	pipe_n = 0;
	while (temp)
	{
		temp->pipe_n = pipe_n;
		if (temp->is_meta && temp->content[0] == '|')
			pipe_n++;
		temp = temp->next;
	}
}
