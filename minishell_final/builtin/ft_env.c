/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:06:28 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/22 19:25:51 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	ft_env(t_cmd *node, t_env *environ)
{
	t_env	*cur;

	if (node->args[0] != NULL)
	{
		cur = environ;
		while (cur != NULL)
		{
			if (cur->export)
			{
				ft_putstr_fd(cur->key, 1);
				ft_putstr_fd("=", 1);
				ft_putstr_fd(cur->val, 1);
				ft_putstr_fd("\n", 1);
			}
			cur = cur->next;
		}
	}
	return (EXIT_SUCCESS);
}
