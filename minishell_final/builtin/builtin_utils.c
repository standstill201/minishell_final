/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:28:31 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/23 17:28:52 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	is_meta_builtin(char c)
{
	if (c == '!' || c == '@' || c == '$' || c == '^' || c == '%' || c == ':' \
	|| c == '*' || c == '[' || c == ']' || c == '/' || c == '{' || c == '}' \
	|| c == ',' || c == '.' || c == '?' || c == '+' || c == '~' || c == '-' \
	|| c == '=' || c == '\\' || c == '#' || c == '&' || c == '*' || c == '\'' \
	|| c == '\"' || c == '`' || c == '(' || c == ')' || c == '|' || c == ';' \
	|| c == '<' || c == '>')
		return (1);
	return (0);
}
