/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:13:04 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/23 17:58:31 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "environ.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

int		ft_echo(t_cmd *node);
int		ft_cd(t_cmd *node, t_env *environ);
int		ft_pwd(t_cmd *node);
int		ft_export(t_cmd *node, t_env *environ);
int		ft_unset(t_cmd *node, t_env *environ);
int		ft_env(t_cmd *node, t_env *environ);
int		ft_exit(t_cmd *node, int process_type);

int		is_meta_builtin(char c);

int		check_export_type(char *cmd);
char	*get_key(char *command);
int		get_value_len(char *command);
char	*get_value(char *command);
void	print_export_value(char *value);

#endif
