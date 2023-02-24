/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 04:24:16 by codespace         #+#    #+#             */
/*   Updated: 2023/02/23 06:39:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_list
{
	char			*content;
	int				pipe_n;
	int				is_meta;
	int				is_single_quote;
	int				is_here_word;
	int				is_fd_new;
	int				is_fd_add;
	int				is_fd_input;
	int				is_question_dollor;
	int				fd;
	struct s_list	*next;
}	t_list;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				fd_out;
	int				fd_in;
	int				fd_old_in;
	int				fd_old_out;
	int				pipe_n;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*val;
	int				export;
	struct s_env	*next;
}	t_env;

#endif
