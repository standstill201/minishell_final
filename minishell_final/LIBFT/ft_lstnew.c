/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      :::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:20:23 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/02/09 07:09:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content, int is_meta)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node -> content = content;
	new_node -> next = NULL;
	new_node -> is_meta = is_meta;
	new_node -> pipe_n = 0;
	new_node -> is_single_quote = 0;
	new_node -> is_question_dollor = 0;
	new_node -> is_here_word = 0;
	new_node -> is_fd_new = 0;
	new_node -> is_fd_add = 0;
	new_node -> is_fd_input = 0;
	new_node -> fd = -2;
	return (new_node);
}
// asdfzxcv$HOME------$HOME2---/$
// asdfzxcv$HOME------
// a$HOME-
