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

void	child_process(int *fds, char *av, char **env, int infile)
{
	char	*cmd_line;
	char	**cmd_vec;

	if (infile < 0)
		exit (1);
	cmd_line = find_path(av, env);
	cmd_vec = make_cmd_vec(av, cmd_line);
	sj_dup2(infile, STDIN_FILENO);
	sj_dup2(fds[1], STDOUT_FILENO);
	sj_close(fds[0]);
	sj_close(fds[1]);
	sj_execve(cmd_line, cmd_vec, env);
}

int	child_open_outfile(char *av, int bonus_n)
{
	int	fd;

	if (bonus_n == 0)
		fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(av, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		write(2, "bash: ", 6);
		write(2, av, ft_strlen(av));
		write(2, ": ", 2);
		perror("");
	}
	return (fd);
}

void	child_last_process(char **av, char **env, int infile, int bonus_n)
{
	int		outfile_fd;
	char	*cmd_line;
	char	**cmd_vec;

	cmd_line = find_path(*av, env);
	cmd_vec = make_cmd_vec(*av, cmd_line);
	outfile_fd = child_open_outfile(*(av + 1), bonus_n);
	if (outfile_fd == -1)
		exit(1);
	sj_dup2(infile, STDIN_FILENO);
	sj_dup2(outfile_fd, STDOUT_FILENO);
	sj_close(infile);
	sj_close(outfile_fd);
	sj_execve(cmd_line, cmd_vec, env);
}

int	ft_wexitstatus(int status)
{
	return (status >> 8 & 0x000000ff);
}

int	free_arr_rtn_sts(int index, int **status_arr, pid_t *pid, int argc)
{
	int	return_val;
	int	innr_index;

	return_val = status_arr[index][1];
	free(pid);
	innr_index = 0;
	while (innr_index < argc - 3)
	{
		free(status_arr[innr_index]);
		innr_index++;
	}
	free(status_arr);
	return (return_val);
}

int	parent_process_wait(int argc, pid_t *pid)
{
	int	index;
	int	**status_arr;
	int	status;

	index = 0;
	status_arr = (int **)malloc(sizeof(int *) * (argc - 3));
	while (index < argc - 3)
	{
		status_arr[index] = (int *)malloc(sizeof(int) * 2);
		status_arr[index][0] = waitpid(-1, &status, 0);
		status_arr[index][1] = ft_wexitstatus(status);
		index++;
	}
	index = 0;
	while (index < argc - 3)
	{
		if (status_arr[index][0] == pid[argc - 4])
			return (free_arr_rtn_sts(index, status_arr, pid, argc));
		index++;
	}
	return (1);
}

void	parent_process(int *infile, int *fds)
{
	if (*infile != -1)
		sj_close(*infile);
	*infile = fds[0];
	sj_close(fds[1]);
}


int	run_process(int ac, char *av[], char **env, int infile)
{
	pid_t	*pid;
	int		fds[2];
	int		index;

	index = 0;
	pid = (int *)malloc(sizeof(pid_t) * (ac - 3));
	while (index < ac - 3)
	{
		if (index != ac - 4)
			pipe(fds);
		pid[index] = sj_fork();
		if (pid[index] == 0 && index != ac - 4)
			child_process(fds, av[index + 2], env, infile);
		else if (pid[index] == 0 && index == ac - 4)
			child_last_process(&av[index + 2], env, infile, 0);
		else if (index != ac - 4)
			parent_process(&infile, fds);
		index++;
	}
	sj_close(infile);
	return (parent_process_wait(ac, pid));
}

int	main(int ac, char *av[], char **env)
{
	int		infile;

	if (ac != 5)
	{
		write(2, "Too few or many arg.\n", 21);
		exit(1);
	}
	infile = read_infile(av[1]);
	return (run_process(ac, av, env, infile));
}
