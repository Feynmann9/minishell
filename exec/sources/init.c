/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpp <jpp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:37:57 by gmarquis          #+#    #+#             */
/*   Updated: 2024/06/07 19:04:32 by jpp              ###   ########.fr       */
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
        (*tmp_base)->command = malloc(sizeof(t_cmd));
        if ((*tmp_base)->command == NULL)
        {
            free(*tmp_base);
            exit(EXIT_FAILURE);
        }
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

void builtin(t_base *base, char **env)
{
    if (base->command->args[1] == NULL)
    {
        if (strcmp(base->command->cmd, "pwd") == 0)
            ft_pwd(&base);
        else if (strcmp(base->command->cmd, "cd") == 0)
            ft_cd(&base, NULL);
        else if (strcmp(base->command->cmd, "env") == 0)
            ft_env(&base);
        else if (find_command(base->command->cmd, get_env_value(base->tmp_env, "PATH")))
            ft_path(base, env);
    }
    else
    {
        if (strcmp(base->command->cmd, "echo") == 0)
            ft_echo(base->command->args[1]);
        else if (strcmp(base->command->cmd, "export") == 0)
            ft_export(&base, base->command->args[1]);
        else if (strcmp(base->command->cmd, "unset") == 0)
            ft_unset(&base, base->command->args[1]);
        else if (strcmp(base->command->cmd, "cd") == 0)
            ft_cd(&base, base->command->args[1]);
        else if (find_command(base->command->cmd, get_env_value(base->tmp_env, "PATH")))
            ft_path(base, env);
    }
}
