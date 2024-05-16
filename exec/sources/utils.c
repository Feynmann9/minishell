/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpp <jpp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:38:32 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/16 16:06:54 by jpp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	ft_lstadd_front_env(t_env **lst, t_env *new)
{

	if (lst == NULL || new == NULL)
		return ;
	else
	{
		new->next = *lst;
		*lst = new;
	}
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

t_env   *ft_lstnew_env(char *name_folder, char *value_folder)
{
    t_env   *new = malloc(sizeof(t_env));
    if (new == NULL)
        return (NULL);
    new->name_folder = name_folder;
    new->value_folder = value_folder;
    new->next = NULL;
    return (new);
}
