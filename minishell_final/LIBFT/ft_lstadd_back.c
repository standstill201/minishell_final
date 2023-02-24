/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:52:43 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/02/09 05:09:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_addr;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_addr = ft_lstlast(*lst);
	last_addr -> next = new;
}
