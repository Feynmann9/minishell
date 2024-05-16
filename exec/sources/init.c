/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpp <jpp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:37:57 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/16 16:08:53 by jpp              ###   ########.fr       */
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

void	init_env(t_env **ev, char **env)
{
    char    **tmp;
    char    **new;

    tmp = env;
    while (*tmp)
    {
        new = ft_split(*tmp, '=', '\n');
        if (new && new[0] && new[1])
            new_env(ev, new[0], new[1]);
        tmp++;
    }
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

void	builtin(t_base **base, char *cmd, char *more)
{
    if (more == NULL)
    {
        if (strcmp(cmd, "pwd") == 0)
            ft_pwd(base);
        if (strcmp(cmd, "cd") == 0)
            ft_cd(base);
        if (strcmp(cmd, "env") == 0)
            ft_env(base);
    }
    if (more != NULL)
    {
        if (strcmp(cmd, "echo") == 0)
            printf("%s\n", more);
        if (strcmp(cmd, "export") == 0)
            ft_export(base, more);
        if (strcmp(cmd, "unset") == 0)
        {
            ft_unset(base, more);
            ft_env(base);
        }
        //else
        //    printf("erreur\n");
    }
}
