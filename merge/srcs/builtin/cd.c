/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:37:21 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/24 23:09:03 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


static void	set_env_value(t_infos *infos, t_env *env, char *name, char *value)
{
	t_env	*new_env;
	t_env	*current;

	while (env)
	{
		if (ft_strcmp(env->name_folder, name) == 0)
		{
			env->value_folder = ft_free_str(env->value_folder);
			env->value_folder = ft_strdup(value);
			if (!env->value_folder)
			{
				value = ft_free_str(value);
				ft_quit(infos, "Error: echec malloc env->value_folder.\n", 2);
			}
			return ;
		}
		env = env->next;
	t_e}
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		ft_quit(infos, "Error: echec malloc new_env.\n", 2);
	new_env->name_folder = ft_strdup(name);
	if (!new_env->name_folder)
		ft_quit(infos, "Error: echec malloc new_env->name_folder.\n", 2);
	new_env->value_folder = ft_strdup(value);
	value = ft_free_str(value);
	if (!new_env->value_folder)
		ft_quit(infos, "Error: echec malloc new_env->value_folder.\n", 2);
	new_env->next = NULL;
	current = env;
	while (current && current->next != NULL)
		current = current->next;
	if (current)
		current->next = new_env;
}

void    ft_cd(t_infos *infos, const char *folder)
{
    char *cd;
    char *cwd;

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
            set_env_value(infos, infos->tmp_env, "PWD", cwd);
        else
            ft_printf("commande introuvable\n");
    }
	if (folder == NULL)
        free(cd);
}

//utiliser chdir pour changer de folder ca permet de le faire auto
//getcwd ca permet de chercher le rep absolue et SEV permet de changer le pwd
