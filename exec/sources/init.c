/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpp <jpp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:37:57 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/23 23:27:08 by jpp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	init(t_base **tmp_base, t_env *ev)
{
    (*tmp_base) = malloc(sizeof(t_base));
    if ((*tmp_base) != NULL)
    {
        (*tmp_base)->tmp_env = ev;
        (*tmp_base)->pid = 0;
        (*tmp_base)->next = NULL;
    }
    else
        exit(EXIT_FAILURE);
}

char	*get_env_value(t_env *env, char *name)
{
    while (env != NULL)
    {
        if (strcmp(env->name_folder, name) == 0)
            return (env->value_folder);
        env = env->next;
    }
    return (NULL);
}
// pour test = ./exec pwd
// pour test = ./exec env
// pour test = ./exec echo "greg le fdp"
// pour test = ./exec export nom="salope" (comment ft_env)

void	builtin(t_base **base, char *cmd, char *more, char **argv, char **env)
{
    if (more == NULL)
    {
        if (strcmp(cmd, "pwd") == 0)
            ft_pwd(base);
        if (strcmp(cmd, "cd") == 0)
            ft_cd(base, NULL);
        if (strcmp(cmd, "env") == 0)
            ft_env(base);
        else if (path_or_notpath(cmd))
            ft_path(base, cmd, argv, env);
    }
    if (more != NULL)
    {
        if (strcmp(cmd, "echo") == 0)
            printf("%s\n", more);
        if (strcmp(cmd, "export") == 0)
        {
            //printf("%s\n", more);
            ft_export(base, more);
        }
        if (strcmp(cmd, "unset") == 0)
        {
            //printf("%s\n", more);
            ft_unset(base, more);
            ft_env(base);
        }
        if (strcmp(cmd, "cd") == 0)
            ft_cd(base, more);
        else if (path_or_notpath(cmd))
            ft_path(base, cmd, argv, env);
        //else
        //    printf("erreur\n");
    }
}
