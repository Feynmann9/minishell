/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpp <jpp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:38:00 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/09 18:35:43 by jpp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	infos->code_error = 0;
}
