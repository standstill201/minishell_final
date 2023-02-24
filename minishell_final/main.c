/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:03:19 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/02/23 09:27:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	g_is_ended;
extern pid_t temp_t;

void	sigint_handler(int sig_num)
{
	if (g_is_ended == -1)
	{
		write(1, "\n", 1);
		close(0);
	}
	else
		write(1, "\n ", 1);
	g_is_ended = 1;
}

void	handle_child_process(t_env *environ, int *status)
{
	char	*line;
	t_cmd	*line_root;
	int		tmp_fd;

	tmp_fd = dup(0);
	g_is_ended = -1;
	printf("cur pid : %d\n", temp_t);
	line = readline("minishell$ ");
	if (g_is_ended > 0)
	{
		dup2(tmp_fd, 0);
		close(tmp_fd);
		return ;
	}
	if (g_is_ended == -1)
		g_is_ended = 0;
	if (!line)
	{
		write(1, "\n", 1);
		exit(0);
	}
	if (line[0] != '\0')
		add_history(line);
	line_root = parse_data(line, status, environ);
	if (!line_root)
	{
		free(line);
		return ;
	}
	t_cmd *temp = line_root;
	char *line_temp;
	int fd;
	while (temp)
	{
		printf("\n--------------------------\n");
		printf("cmd:%s$\n", temp->cmd);
		for (int i = 0; temp->args[i]; i++)
			printf("args%d:%s$\n", i, temp->args[i]);
		printf("fd_in: %d\n", temp->fd_in);
		printf("fd_out: %d\n", temp->fd_out);
		printf("pipe_n: %d\n", temp->pipe_n);
		printf("\n--------------------------\n");
		temp = temp->next;
	}
	*status = run_process(line_root, environ);
	free(line);
}


int	main(int argc, char **argv, char **envp)
{
	t_env	*environ;
	int		status;

	status = 0;
	environ = set_environ(envp);
	signal(SIGINT, sigint_handler);
	while (1)
	{
		g_is_ended = 0;
		handle_child_process(environ, &status);
	}
	return (0);
}
