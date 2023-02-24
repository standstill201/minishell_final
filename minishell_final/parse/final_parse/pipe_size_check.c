/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_size_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 07:35:45 by codespace         #+#    #+#             */
/*   Updated: 2023/02/23 07:37:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipe_size_check(t_list *pre_temp, t_list *temp)
{
	int	index;

	index = 0;
	while (pre_temp != temp)
	{
		if (pre_temp && pre_temp->is_meta == 0 && pre_temp->is_here_word == 0
			&& pre_temp->is_fd_input == 0 && pre_temp->is_fd_new == 0
			&& pre_temp->is_fd_add == 0)
			index++;
		pre_temp = pre_temp->next;
		if (pre_temp && pre_temp->is_meta == 0 && pre_temp->is_here_word == 0
			&& pre_temp->is_fd_input == 0 && pre_temp->is_fd_new == 0
			&& pre_temp->is_fd_add == 0 && pre_temp == temp)
			index++;
	}
	return (index);
}
