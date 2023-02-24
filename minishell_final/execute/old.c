#include "../include/execute.h"

pid_t temp[2];

int	execute_builtin(t_cmd *node, t_env *environ, int process_type)
{
	int	ret;

	ret = -1;
	if (node->cmd == NULL)
		return (ret);
	if (ft_strncmp(node->cmd, "echo", 5) == 0)
		ret = ft_echo(node);
	else if (ft_strncmp(node->cmd, "cd", 3) == 0)
		ret = ft_cd(node, environ);
	else if (ft_strncmp(node->cmd, "pwd", 4) == 0)
		ret = ft_pwd(node);
	else if (ft_strncmp(node->cmd, "export", 7) == 0)
		ret = ft_export(node, environ);
	else if (ft_strncmp(node->cmd, "unset", 6) == 0)
		ret = ft_unset(node, environ);
	else if (ft_strncmp(node->cmd, "env", 4) == 0)
		ret = ft_env(node, environ);
	else if (ft_strncmp(node->cmd, "exit", 5) == 0)
		ret = ft_exit(node, process_type);
	return (ret);
}

int	execute_command_type(t_cmd *node, t_env *environ, int process_type)
{
	struct stat	sb;
	pid_t		pid;

	if (execute_builtin(node, environ, process_type) == -1)
	{
		pid = fork();
		if (pid == -1)
			execute_error("failed to fork", process_type);
		else if (pid == 0)
		{
			if (stat(node->cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
				is_a_directory(node->cmd);
			if (execute_command(node, get_environ(environ)) == 1)
				command_not_found(node->cmd);
			else
				exit(0);
		}
		else
			if (waitpid(pid, NULL, 0) == -1)
				execute_error("failed to waitpid", process_type);
	}
	reset_fd(node, process_type);
	return (0);
}

void	pipeline_child(t_cmd *node, t_env *environ)
{
	int		pfd[2];
	pid_t	pid;

	// if (node->fd_in != -2)
	// 	dup2(node->fd_in, STDIN_FILENO);
	// else
	// 	node->fd_in = dup(STDIN_FILENO);
	// if (node->fd_out != -2)
	// 	dup2(node->fd_out, STDOUT_FILENO);
	// else
	// 	node->fd_out = dup(STDOUT_FILENO);
	
	ft_pipe(pfd);
	pid = fork();
	temp[0] = pid;
	if (pid == -1)
		execute_error("failed to fork", CHILD);
	else if (pid == 0)
	{
		if (node->fd_in != -2)
			ft_dup2(node->fd_in, STDIN_FILENO, CHILD);
		ft_close(pfd[READ_END], CHILD);
		ft_dup2(pfd[WRITE_END], STDOUT_FILENO, CHILD);
		if (node->fd_out != -2)
			ft_dup2(node->fd_out, STDOUT_FILENO, CHILD);
		if (execute_command_type(node, environ, CHILD) == 1)
			command_not_found(node->cmd);
		else
			exit(0);
	}
	else
	{
		ft_close(pfd[WRITE_END], CHILD);
		ft_dup2(pfd[READ_END], STDIN_FILENO, CHILD);
	}
}

void	pipeline(t_cmd *node, t_env *environ)
{
	t_cmd	*cur;
	int		save;

	cur = node;
	while (cur->next != NULL)
	{
		pipeline_child(cur, environ);
		cur = cur->next;
	}
	// fork
	// if child
	if (cur->fd_in != -2)
		ft_dup2(cur->fd_in, STDIN_FILENO, PARENT);
	if (cur->fd_out != -2)
		ft_dup2(cur->fd_out, STDOUT_FILENO, PARENT);
	if (execute_command_type(cur, environ, PARENT) == 1)
		command_not_found(cur->cmd);
	else
		exit(0);

	// if parent
	waitpid(temp[0], NULL, 0);	
}
#include <stdio.h>
int	execute(t_cmd *line, t_env *environ)
{
	t_cmd	*node;
	pid_t	pid;
	char	**envp;

	if (line == NULL)
		return (1);
	node = line;
	if (node->next == NULL)
	{
		set_fd(node);
		return (execute_command_type(node, environ, PARENT));
	}
	else
	{
		pipeline(node, environ);
	}
	return (0);
}
