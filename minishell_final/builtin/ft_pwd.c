/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:25:17 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/22 16:44:44 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	ft_pwd(t_cmd *node)
{
	char	*path;

	if (node == NULL)
		return (EXIT_FAILURE);
	path = getcwd(NULL, 0);
	if (path == NULL)
		return (EXIT_FAILURE);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	free(path);
	return (EXIT_SUCCESS);
}
