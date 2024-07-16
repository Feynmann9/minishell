/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:38:00 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/16 15:07:47 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*void ft_unset(t_base **base, char *more) // Attention pd utilise un char ** pour le cas ou il y a plusieurs argument (Charles a dit)
{
	t_env *current = (*base)->tmp_env;

	while (current)
	{
		if (strcmp(current->name_folder, more) == 0)
		{
			free(current->name_folder);
			free(current->value_folder);
			free(current);
			return ;
		}
		current = current->next;
	}
}*/

void	ft_unset(t_infos *infos, char *more)
{
	t_env *current = infos->tmp_env;
	t_env *prev = NULL;

	while (current)
	{
		if (strcmp(current->name_folder, more) == 0)
		{
			if (prev)
			{
				prev->next = current->next;
			}
			else
			{
				infos->tmp_env = current->next;
			}
			free(current->name_folder);
			free(current->value_folder);
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}
