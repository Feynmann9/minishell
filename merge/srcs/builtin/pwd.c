/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:37:51 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/16 13:38:23 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*utilise la fonction getcwd de <unistd.h> ca te donne le cwd "current working directory" dirctement PD*/

void	ft_pwd(t_infos *infos)
{
	char	*pwd;

	pwd = get_env_value(infos->tmp_env, "PWD");
	if (pwd != NULL)
		ft_printf("%s\n", pwd);
	else
		ft_printf("commande introuvable\n");
}
