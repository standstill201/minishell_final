/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_for_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:00:12 by codespace         #+#    #+#             */
/*   Updated: 2023/02/23 08:13:30 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*line_backup_realloc(char *buffer, char *backup, char *line, int fd)
{
	int	read_size;

	line = re_allocate(buffer, line);
	backup_maker(buffer, &backup);
	return (line);
}

int	sigint_case(int tmp_fd)
{
	dup2(tmp_fd, 0);
	close(tmp_fd);
	return (0);
}
