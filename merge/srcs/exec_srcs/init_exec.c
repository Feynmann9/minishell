/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:37:57 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/15 22:37:14 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../merge.h"

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
        (*tmp_base)->command->cmd = NULL;
        (*tmp_base)->command->more = NULL;
        (*tmp_base)->command->args = NULL;
        (*tmp_base)->command->pipe = 0;
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

void builtin(t_infos *infos, char **env)
{
    if (infos->tok->cmd[1] == NULL)
    {
        if (strcmp(infos->tok->cmd[0], "pwd") == 0)
            ft_pwd(&base);
        else if (strcmp(infos->tok->cmd[0], "cd") == 0)
            ft_cd(&base, NULL);
        else if (strcmp(infos->tok->cmd[0], "env") == 0)
            ft_env(&base);
        else if (strcmp(infos->tok->cmd[0], "exit") == 0)
            exit(EXIT_FAILURE);
        else if (strcmp(infos->tok->cmd[0], "export") == 0)
        {
            ft_order_env(&base);
            ft_print_order(&base);
        }
        else if (find_command(base->command->cmd, get_env_value(infos->tmp_env, "PATH")) && infos->tok->NEXT != 0)
        {
            //printf("test1\n");
            ft_multi(base, env);
        }
        else if (find_command(base->command->cmd, get_env_value(base->tmp_env, "PATH")))
            ft_path(base, env);
    }
    else
    {
        if (strcmp(infos->tok->cmd[0], "echo") == 0)
            ft_echo(base->command->args);
        else if (strcmp(infos->tok->cmd[0], "export") == 0)
            ft_export(&base, base->command->args[1]);
        else if (strcmp(infos->tok->cmd[0], "unset") == 0)
            ft_unset(&base, base->command->args[1]);
        else if (strcmp(infos->tok->cmd[0], "cd") == 0)
            ft_cd(&base, base->command->args[1]);
        else if (find_command(infos->tok->cmd[0], get_env_value(infos->tmp_env, "PATH")) && infos->tok->NEXT != 0)
        {
            //printf("test2\n");
            ft_multi(base, env);
        }
        else if (find_command(infos->tok->cmd[0], get_env_value(infos->tmp_env, "PATH")))
            ft_path(base, env);
    }
}
