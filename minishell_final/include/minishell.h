/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:04:12 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/02/23 09:23:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

# include "../LIBFT/libft.h"
# include "execute.h"
# include "environ.h"

# define LINE_SPILL 0

extern int	g_is_ended;

// parse_part
t_cmd	*parse_data(char *str, int *status, t_env *environ);
t_list	*seperate_string(char *str, int *status);
void	set_pipe_n(t_list **root);
void	set_env(t_list **root, int *status, t_env *environ);
void	*same_file(t_list **root);
// heredoc_part
int		set_here(t_list **pre_parse, int *status);
int		read_heredoc_infile(char *limiter, t_list *temp, int *status);
int		create_temp_file(void);
// heredoc_part end

// merge_string_part
t_list	*merge_string(t_list **root);
t_list	*meta_add(t_list *temp, t_list **return_val);
// merge_string_part end

// meta_parse_part
char	*parse_meta(char *str, t_list **root, int *status);
int		is_meta(char c);
int		double_quote_task(char *return_val, t_list **root, int *status);
char	*read_string_before_redirection(char *str, t_list **root);
char	*read_string_before_dollar(char *str, t_list **root, int *status);
// meta_parse_part end

// redirection_part
int		del_redi_read_here(t_list **merged_lst, int *status);
// redirection_part end

// final_parse_part
t_cmd	*ft_lstnew_cmd(char *cmd, char **args);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
int		pipe_size_check(t_list *pre_temp, t_list *temp);
t_cmd	*final_parse(t_list **pre_lst);
// final_parse_part end

// parse_part end

// execute_part
void	organize_execute(t_list **root);
// execute_part end

// error_handle_part
int		minishell_error(char *error_msg, int *status);
int		unexpected_token_error(char *token, int *status);
int		unexpected_token_newline(int *status);
int		unexpected_token_end(int *status);
// error_handle_part end

// gnl
char	*line_backup_realloc(char *buffer, char *backup, char *line, int fd);
char	*re_allocate(char *buffer, char *line);
void	backup_maker(char *buffer, char **backup);
int		sigint_case(int tmp_fd);
char	*get_next_line(int fd, int trg);
// gnl end

#endif
