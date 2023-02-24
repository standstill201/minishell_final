/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:43:32 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/23 17:59:44 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	ft_close(int fd, int process_type)
{
	if (close(fd) == -1)
		return (execute_error("failed to close", process_type));
}

int	ft_dup2(int fd1, int fd2, int process_type)
{
	if (dup2(fd1, fd2) == -1)
		return (execute_error("falied to dup2", process_type));
	if (fd1 != -2)
		return (ft_close(fd1, process_type));
}

int ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
		return (execute_error("failed to pipe", CHILD));
}

int	ft_waitpid(pid_t pid, int *statloc, int options)
{
	if (waitpid(pid, statloc, options) == -1)
		return (execute_error("failed to waitpid", PARENT));
}
