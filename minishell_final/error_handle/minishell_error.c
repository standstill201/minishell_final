/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:53:47 by codespace         #+#    #+#             */
/*   Updated: 2023/02/23 08:22:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	minishell_error(char *error_msg, int *status)
{
	write(2, "minishell: ", 11);
	write(2, error_msg, ft_strlen(error_msg));
	write(2, ": ", 2);
	perror("");
	*status = 1;
	return (1);
}

int	unexpected_token_error(char *token, int *status)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
	*status = 2;
	return (1);
}

int	unexpected_token_newline(int *status)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
	*status = 2;
	return (1);
}

int	unexpected_token_end(int *status)
{
	ft_putstr_fd("minishell: syntax error not ended quote\n", 2);
	*status = 1;
	return (1);
}
