/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:06:26 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/20 17:52:45 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# include "minishell.h"
# include "struct.h"

t_env	*env_lstnew(char **envp);
t_env	*env_lstlast(t_env *envs);
void	env_lstadd_back(t_env **environ, t_env *new);
void	env_lstclear(t_env *environ);
int		env_lstlen(t_env *environ);
t_env	*set_environ(char **envp);
void	add_environ(t_env *environ, char *key, char *val, int export);
void	delete_environ(t_env *environ, char *key);
char	**get_environ(t_env *environ);
char	*get_env(t_env *environ, char *key);

#endif
