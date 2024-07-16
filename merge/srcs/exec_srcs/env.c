/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:28:54 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/16 13:50:05 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_env(t_base **base)
{
	t_env *tmp;

	if (!(tmp = malloc(sizeof(t_env))))
		return ;
	tmp = (*base)->tmp_env;
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->name_folder, tmp->value_folder);
		tmp = tmp->next;
	}
}
