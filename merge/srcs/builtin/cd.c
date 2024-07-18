/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:37:21 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/18 19:11:28 by gmarquis         ###   ########.fr       */
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
	}
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

void	ft_cd(t_infos *infos, char *folder)
{
	char	*cd;

	int (buf_size) = BUFFER_SIZE;
	char *(cwd) = malloc(buf_size);
	if (!cwd)
		ft_quit(infos, "Error: echec malloc cwd.\n", 2);
	if (folder == NULL)
		cd = get_env_value(infos->tmp_env, "HOME");
	else
	{
		cd = ft_strdup(folder);
		if(!cd)
			ft_quit(infos, "Error: echec malloc cd.\n", 2);
	}
	if (chdir(cd) != 0)
		ft_printf("commande introuvable\n");
	else
	{
		while (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			if (errno == ERANGE)		// Si le buffer est trop petit
			{
				cwd = ft_realloc(cwd, ft_strlen(cwd) + 1, buf_size);
				if (!cwd)
					ft_quit(infos, "Error: echec realloc cwd.\n", 2);
				buf_size += BUFFER_SIZE;
			}
			else
			{
				ft_printf("commande introuvable\n");
				free(cwd);
				cwd = NULL;
				break ;
			}
		}
		set_env_value(infos, infos->tmp_env, "PWD", cwd);
	}
}

//utiliser chdir pour changer de folder ca permet de le faire auto
//getcwd ca permet de chercher le rep absolue et SEV permet de changer le pwd
