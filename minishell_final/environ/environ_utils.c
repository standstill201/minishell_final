/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:07:16 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/23 17:28:02 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/environ.h"

t_env	*env_lstnew(char **envp)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = envp[0];
	new->val = envp[1];
	new->export = 1;
	new->next = NULL;
	return (new);
}

t_env	*env_lstlast(t_env *envs)
{
	if (envs == NULL)
		return (NULL);
	while (envs->next != NULL)
		envs = envs->next;
	return (envs);
}

void	env_lstadd_back(t_env **environ, t_env *new)
{
	t_env	*cur;

	if (environ == NULL || new == NULL)
		return ;
	if (*environ == NULL)
	{
		*environ = new;
		return ;
	}
	cur = env_lstlast(*environ);
	cur->next = new;
	new->next = NULL;
}

void	env_lstclear(t_env *environ)
{
	t_env	*cur;
	t_env	*tmp;

	if (environ == NULL)
		return ;
	cur = environ;
	while (cur != NULL)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp->key);
		free(tmp->val);
		free(tmp);
	}
	environ = NULL;
}

int	env_lstlen(t_env *environ)
{
	t_env	*cur;
	int		len;

	if (environ == NULL)
		return (0);
	len = 0;
	cur = environ;
	while (cur != NULL)
	{
		cur = cur->next;
		len++;
	}
	return (len);
}
