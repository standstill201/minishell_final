/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:25:50 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/22 20:25:11 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	is_numeric(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_exit(t_cmd *node, int process_type)
{
	int	status;

	if (node->args[0] != NULL)
	{
		if (process_type == 2)
			ft_putstr_fd("exit\n", 2);
		if (node->args[1] != NULL)
		{
			if (!is_numeric(node->args[1]))
				exit(255);
			if (node->args[2] != NULL)
			{
				ft_putstr_fd("minishell: exit: too many arguments", 2);
				return (1);
			}
			status = ft_atoi(node->args[1]);
			exit(status);
		}
		exit(0);
	}
	return (1);
}
