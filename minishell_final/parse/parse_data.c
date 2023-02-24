/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 05:55:43 by codespace         #+#    #+#             */
/*   Updated: 2023/02/23 09:29:29 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*error_seperate(t_list *parse_seperate)
{
	t_cmd	*return_val;

	ft_lstclear(&parse_seperate, free);
	return_val = NULL;
	return (return_val);
}

t_cmd	*parse_data(char *str, int *status, t_env *environ)
{
	t_list	*parse_seperate;
	t_cmd	*return_val;
	int		index;

	index = 0;
	parse_seperate = seperate_string(str, status);
	if (!parse_seperate)
		return (error_seperate(parse_seperate));
	if (set_here(&parse_seperate, status))
		return (error_seperate(parse_seperate));
	set_pipe_n(&parse_seperate);
	set_env(&parse_seperate, status, environ);
	if (ft_lstlast(parse_seperate)->content[0] == '|'
		&& ft_lstlast(parse_seperate)->is_meta == 1)
	{
		ft_putstr_fd("minishell: not ended token `|'\n", 2);
		*status = 1;
		return (error_seperate(parse_seperate));
	}
	parse_seperate = merge_string(&parse_seperate);
	if (del_redi_read_here(&parse_seperate, status))
		return (error_seperate(parse_seperate));
	return_val = final_parse(&parse_seperate);
	return (return_val);
}
