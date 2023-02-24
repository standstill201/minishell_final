/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_parse_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:23:52 by codespace         #+#    #+#             */
/*   Updated: 2023/02/22 03:32:13 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*ft_lstnew_cmd(char *cmd, char **args)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->args = args;
	new->next = NULL;
	new->fd_in = 0;
	new->fd_out = 0;
	new->fd_old_in = -2;
	new->fd_old_out = -2;
	new->pipe_n = 0;
	return (new);
}

t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	t_cmd	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*temp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast_cmd(*lst);
	temp->next = new;
}
