/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:28:54 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/18 19:35:21 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_infos *infos)
{
	t_env	*tmp;

	tmp = infos->tmp_env;
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->name_folder, tmp->value_folder);
		tmp = tmp->next;
	}
}
