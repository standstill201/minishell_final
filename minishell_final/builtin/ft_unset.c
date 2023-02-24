/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:22:00 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/23 17:32:35 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	meta_exist(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (is_meta_builtin(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(t_cmd *node, t_env *environ)
{
	int	i;

	i = 1;
	while (node->args[i] != NULL)
	{
		if (meta_exist(node->args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(node->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		delete_environ(environ, node->args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
