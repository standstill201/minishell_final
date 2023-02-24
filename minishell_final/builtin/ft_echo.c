/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:55:27 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/21 16:53:14 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	check_option(char *option)
{
	int	i;

	if (ft_strncmp(option, "-n", 2) == 0)
	{
		i = 2;
		while (option[i] != '\0')
		{
			if (option[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

int	ft_echo(t_cmd *node)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (node->args[i] && check_option(node->args[i]))
	{
		option = 1;
		i++;
	}
	while (node->args[i])
	{
		ft_putstr_fd(node->args[i], 1);
		if (node->args[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!option)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}
