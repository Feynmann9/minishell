/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpp <jpp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:37:21 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/09 18:35:12 by jpp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_env_value(t_infos *infos, t_env *env, char *name, char *value)
{
	if (!value)
		return ;
	while (env)
	{
		if (ft_strcmp(env->name_folder, name) == 0)
		{
			env->value_folder = ft_free_str(env->value_folder);
			env->value_folder = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	t_env (*new_env) = malloc(sizeof(t_env));
	if (!new_env)
		ft_quit(infos, "Error: echec malloc new_env.\n", 2);
	new_env->name_folder = ft_strdup(name);
	new_env->value_folder = ft_strdup(value);
	value = ft_free_str(value);
	if (!new_env->value_folder || !new_env->name_folder)
		ft_quit(infos, "Error: echec malloc new_env->value_folder.\n", 2);
	new_env->next = NULL;
	t_env (*current) = env;
	while (current && current->next != NULL)
		current = current->next;
	if (current)
		current->next = new_env;
}

void	ft_cd(t_infos *infos, const char *folder)
{
	char	*cd;
	char	*cwd;

	if (folder == NULL)
		cd = get_env_value(infos->tmp_env, "HOME");
	else
		cd = ft_strdup(folder);
	if (chdir(cd) != 0)
		ft_printf("commande introuvable\n");
	else
	{
		cwd = getcwd(NULL, 0);
		if (cwd != NULL)
		{
			set_env_value(infos, infos->tmp_env, "PWD", cwd);
			free(cwd);
		}
		else
			ft_printf("commande introuvable\n");
	}
	infos->code_error = 0;
	if (folder == NULL)
		free(cd);
}

//utiliser chdir pour changer de folder ca permet de le faire auto
//getcwd ca permet de chercher le rep absolue et SEV permet de changer le pwd
