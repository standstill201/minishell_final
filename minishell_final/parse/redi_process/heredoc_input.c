/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:07:03 by codespace         #+#    #+#             */
/*   Updated: 2023/02/23 09:49:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	up_digit(char *str, int index)
{
	str[index] = '!';
	if (index > 0)
	{
		if (str[index - 1] == '~')
			up_digit(str, index - 1);
		else
			str[index - 1]++;
	}
}

char	*name_creator(void)
{
	char	*str;
	int		index;
	char	*return_val;

	str = ft_strdup("!!!!!");
	return_val = ft_strjoin("/tmp/", str);
	index = ft_strlen(return_val) - 1;
	free(str);
	while (access(return_val, F_OK) == 0)
	{
		if (return_val[index] == '~')
			up_digit(return_val, index);
		else
			return_val[index]++;
		if (return_val[index] == '/')
			return_val[index] = 'f';
	}
	return (return_val);
}

void	free_everything(char *str, int fd)
{
	unlink(str);
	free(str);
	close(fd);
}

int	g_is_ended_case(int *status, char *str, int fd)
{
	if (g_is_ended == -1)
		g_is_ended = 0;
	if (g_is_ended)
	{
		free_everything(str, fd);
		*status = 130;
		return (1);
	}
	return (0);
}

int	read_heredoc_infile(char *limiter, t_list *temp, int *status)
{
	int		fd;
	char	*line;
	char	*str;

	str = name_creator();
	fd = open(str, O_CREAT | O_RDWR, 0644);
	line = get_next_line(STDIN_FILENO, 1);
	if (g_is_ended_case(status, str, fd))
		return (-2);
	while (line && ft_strncmp(line, limiter, ft_strlen(line)))
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO, 1);
		if (g_is_ended_case(status, str, fd))
			return (-2);
	}
	close(fd);
	fd = open(str, O_RDONLY);
	unlink(str);
	free(str);
	free(line);
	return (fd);
}
