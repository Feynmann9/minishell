/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:39:09 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/07 18:56:19 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env_value(t_env *env, char *name)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->name_folder, name) == 0)
			return (env->value_folder);
		env = env->next;
	}
	return (NULL);
}

void	ft_make_env(t_infos *infos, t_env **tmp_env, char **env_var)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name_folder = ft_strdup(env_var[0]);
	if(!new->name_folder)
		ft_quit(infos, "Error: echec malloc new->name_folder.\n", 2);
	new->value_folder = ft_strdup(env_var[1]);
	if(!new->value_folder)
		ft_quit(infos, "Error: echec malloc new->value_folder.\n", 2);
	new->next = NULL;
	ft_lstadd_back_env(tmp_env, &new);
}

char	**ft_split_env(t_infos *infos, char *ligne)
{
	char	**env_var;

	int (i) = 0;
	int (j) = 0;
	int (len_name) = ft_countuntil(ligne, '=');
	int (len_value) = (ft_strlen(ligne) - len_name) - 1;
	env_var = malloc(3 * sizeof(char *));
	if (!env_var)
		ft_quit(infos, "Error: echec malloc env_var**.\n", 2);
	env_var[2] = NULL;
	env_var[0] = malloc(len_name * sizeof(char) + 1);
	if (!env_var[0])
		ft_quit(infos, "Error: echec malloc env_var[0].\n", 2);
	env_var[1] = malloc(len_value * sizeof(char) + 1);
	if (!env_var[1])
		ft_quit(infos, "Error: echec malloc env_var[1].\n", 2);
	while (ligne[i] != '=')
	{
		env_var[0][i] = ligne[i];
		i++;
	}
	env_var[0][i++] = '\0';
	while (ligne[i])
		env_var[1][j++] = ligne[i++];
	return (env_var[1][j] = '\0', env_var);
}

char	**ft_null_env(t_infos *infos)
{
	char	**env;

	env = malloc(3 * sizeof(char *));
	if (!env)
		ft_quit(infos, "Error: echec malloc env.\n", 2);
	env[0] = malloc(4);
	if (!env[0])
		ft_quit(infos, "Error: echec malloc env[0].\n", 2);
	ft_strcpy(env[0], "PWD");
	env[1] = getcwd(NULL, 0);
	if (!env[1])
		ft_quit(infos, "Error: echec getcwd env[1].\n", 2);
	env[2] = NULL;
	return (env);
}

t_env	*ft_init_env(t_infos *infos, char **env)
{
	t_env	*tmp_env;
	char	**env_var;
	int		i;

	tmp_env = NULL;
	i = 0;
	if (!env[0])
	{
		env_var = ft_null_env(infos);
		ft_make_env(infos, &tmp_env, env_var);
		env_var = ft_free_tab2d(env_var);
		add_export(tmp_env, "SHLVL", "1");
		add_export(tmp_env, "_", "");
		infos->tmp_path = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
	}
	else
	{
		while (env[i])
		{
			env_var = ft_split_env(infos, env[i]);
			ft_make_env(infos, &tmp_env, env_var);
			env_var = ft_free_tab2d(env_var);
			i++;
		}
	}
	return (tmp_env);
}
