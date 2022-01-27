/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:32:15 by sachmull          #+#    #+#             */
/*   Updated: 2021/07/09 15:33:19 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	void	*content;

	(void)del;
	new_lst = 0;
	while (lst)
	{
		content = ft_lstnew((*f)(lst->content));
		if (content != NULL)
			ft_lstadd_back(&new_lst, content);
		lst = lst->next;
	}
	return (new_lst);
}
