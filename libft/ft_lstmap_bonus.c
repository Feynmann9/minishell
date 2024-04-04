/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matran-d <matran-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:59:03 by matran-d          #+#    #+#             */
/*   Updated: 2023/11/10 14:59:03 by matran-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*listnew;
	t_list	*listnull;

	listnull = NULL;
	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		listnew = ft_lstnew(f(lst->content));
		if (!listnew)
		{
			ft_lstclear(&listnull, del);
			return (0);
		}
		ft_lstadd_back(&listnull, listnew);
		lst = lst->next;
	}
	return (listnull);
}
