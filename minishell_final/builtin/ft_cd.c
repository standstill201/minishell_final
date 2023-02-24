/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:49:01 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/21 14:42:10 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	ft_cd(t_cmd *node, t_env *environ)
{
	char	*cwd;
	int		ret;

	if (node->args[1] == NULL)
	{
		if (chdir(get_env(environ, "HOME")) == -1)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	if (chdir(node->args[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(node->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
