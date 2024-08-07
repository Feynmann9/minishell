/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:38:32 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/18 21:17:02 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	ft_lstadd_back_env(t_env **lst, t_env **new)
{
	t_env	*temp;

	if (*lst == NULL)
	{
		*lst = *new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = *new;
}
