/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:19:23 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/23 17:47:50 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include "environ.h"
# include "builtin.h"
# include <sys/wait.h>
# include <sys/stat.h>

# define READ_END	0
# define WRITE_END	1
# define PARENT	2
# define CHILD	4

int		execute_error(char *message, int process_type);
void	execute_command_error(char *command);
void	command_not_found(char *command);
void	is_a_directory(char *command);

char	*find_path(char *command, char **envp);
int		execute_command(t_cmd *node, char **envp);
int		execute(t_cmd *commandline, t_env *environ);

void	set_fd(t_cmd *node, int process_type);
void	reset_fd(t_cmd *node, int process_type);

int		ft_close(int fd, int process_type);
int		ft_dup2(int fd1, int fd2, int process_type);
int		ft_pipe(int *fd);
int		ft_waitpid(pid_t pid, int *statloc, int options);


int	run_process(t_cmd *line_root, t_env *environ);

#endif
