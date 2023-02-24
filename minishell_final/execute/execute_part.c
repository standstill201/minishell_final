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

#include "../include/execute.h"

int	ft_wexitstatus(int status)
{
	return (status >> 8 & 0x000000ff);
}

int	is_white(char c)
{
	if (c == '\n' || c == '\t' || c == '\f' || c == '\r'
		|| c == '\v' || c == ' ')
		return (1);
	else
		return (0);
}

char	**path_finder(char **env)
{
	int		index;
	char	**return_val;

	index = 0;
	while (env[index])
	{
		if (env[index][0] == 'P' && env[index][1] == 'A'
		&& env[index][2] == 'T' && env[index][3] == 'H')
			return (ft_split(&env[index][5], ':'));
		index++;
	}
	return_val = (char **)malloc(sizeof(char *) * 1);
	return_val[0] = (char *)malloc(sizeof(char));
	return_val[0][0] = 0;
	return (return_val);
}

void	free_str(char **str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		free(str[index]);
		index++;
	}
	free(str);
}

char	*del_blank(char *av)
{
	int		index;
	int		index_point;

	index = 0;
	while (av[index] && is_white(av[index]))
		index++;
	if (!av[index])
		return (NULL);
	index_point = index;
	while (av[index] && !is_white(av[index]))
		index++;
	return (ft_substr(av, index_point, index - index_point));
}

char	*find_path_cmd(char *av, char **env)
{
	char	*return_val;
	char	**path_addr;
	char	*av_no_bl;
	int		index;

	if (access(av, 1) == 0)
		return (av);
	index = 0;
	path_addr = path_finder(env);
	av_no_bl = del_blank(av);
	while (path_addr[index])
	{
		return_val = ft_strjoin(path_addr[index], av_no_bl);
		if (access(return_val, 1) == 0)
		{
			free_str(path_addr);
			return (return_val);
		}
		free(return_val);
		index++;
	}
	return (av_no_bl);
}


t_cmd	*ft_lstlast_execute(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

int	free_arr_rtn_sts(int index, int **status_arr, pid_t *pid, int cmd_size)
{
	int	return_val;
	int	innr_index;

	return_val = status_arr[index][1];
	free(pid);
	innr_index = 0;
	while (innr_index < cmd_size)
	{
		free(status_arr[innr_index]);
		innr_index++;
	}
	free(status_arr);
	return (return_val);
}

void	child_process(int *fds, t_cmd *temp, char **env, int infile)
{
	char	*cmd_line;
	char	**cmd_vec;

	cmd_line = find_path_cmd(temp->cmd, env);
	cmd_vec = temp->args;
	dup2(infile, STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[0]);
	close(fds[1]);
	execve(cmd_line, cmd_vec, env);

	/// need env
}

int	parent_process_wait(int cmd_size, pid_t *pid)
{
	int	index;
	int	**status_arr;
	int	status;

	index = 0;
	status_arr = (int **)malloc(sizeof(int *) * cmd_size);
	while (index < cmd_size)
	{
		status_arr[index] = (int *)malloc(sizeof(int) * 2);
		status_arr[index][0] = waitpid(-1, &status, 0);
		status_arr[index][1] = ft_wexitstatus(status);
		index++;
	}
	index = 0;
	while (index < cmd_size)
	{
		if (status_arr[index][0] == pid[cmd_size - 1])
			return (free_arr_rtn_sts(index, status_arr, pid, cmd_size));
		index++;
	}
	return (1);
}

int	infile_finder(t_cmd *temp, int infile)
{
	if (!temp->pipe_n)
		return (temp->fd_in);
	if (temp->fd_in == -2 && infile > -1)
		return (infile);
	else if (temp->fd_in > 0)
		return (temp->fd_in);
}

void	parent_process(int *infile, int *fds)
{
	if (*infile != -1)
		close(*infile);
	*infile = fds[0];
	close(fds[1]);
}

char	**env_creator(t_env *environ)
{
	char	**return_val;
	t_env	*temp;
	int		index;

	index = 0;
	temp = environ;
	while (temp)
	{
		index++;
		temp = temp->next;
	}
	return_val = (char **)malloc(sizeof(char *) * (index + 1));
	index = 0;
	temp = environ;
	while (temp)
	{
		return_val[index] = ft_strjoin(environ->key, environ->val);
		index++;
		temp = temp->next;
	}
	return (return_val);
}

int	run_process(t_cmd *line_root, t_env *environ)
{
	pid_t	*pid;
	int		fds[2];
	int		index;
	int		infile;
	int		cmd_size;
	t_cmd	*temp;
	char	**env;

	index = 0;
	temp = line_root;
	cmd_size = ft_lstlast_execute(line_root)->pipe_n + 1;
	pid = (int *)malloc(sizeof(pid_t) * cmd_size);
	env = env_creator(environ);
	infile = temp->fd_in;
	while (index < cmd_size)
	{
		if (index != cmd_size - 1)
			pipe(fds);
		infile = infile_finder(temp, infile);
		pid[index] = fork();
		if (pid[index] == 0)
			child_process(fds, temp, env, infile);
		else if (index != cmd_size - 1)
			parent_process(&infile, fds);
		index++;
		temp = temp->next;
	}
	close(infile);
	return (parent_process_wait(cmd_size, pid));
}
