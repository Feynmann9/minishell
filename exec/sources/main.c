/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpp <jpp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:39:09 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/17 17:18:51 by jpp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void    new_env(t_env **ev, char *name_folder, char *value_folder)
{
    t_env *tmp;

    if (!(tmp = malloc(sizeof(t_env))))
        return ;
    tmp->name_folder = ft_strdup(name_folder);
    tmp->value_folder = ft_strdup(value_folder);
    if (*ev != NULL)
        ft_lstadd_back_env(ev, tmp);
    else
        ft_lstadd_front_env(ev, tmp);
}

void	print_env(t_env *ev)
{
    while (ev)
    {
        if (strcmp(ev->name_folder, "PWD") == 0)
            printf("%s\n", ev->value_folder);
        ev = ev->next;
    }
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

void split_input(char *input, char **cmd, char **args)
{
    int i = 0;
    *cmd = input;

    while (input[i] != ' ' && input[i] != '\0')
        i++;
    if (input[i] == '\0')
        *args = NULL;
    else
    {
        input[i] = '\0';
        *args = input + i + 1;
    }
}

int main(int argc, char **argv, char **env)
{
    t_env *ev = NULL;
    t_base *base = NULL;
    char *input;
    (void)argv;
    if (argc > 3)
    {
        ft_printf("\033[32mToo many argc, sorry\033[0m\n");
        return (0);
    }
    init_env(&ev, env);
    init(&base, ev);
    while (1)
    {
        input = readline("\033[32mCumShell $> \033[0m");
        if (!input)
            break ;
        char *cmd;
        char *args;
        split_input(input, &cmd, &args);
        builtin(&base, cmd, args);
        free(input);
    }
    //builtin(&base, argv[1], argv[2]);
    return (0);
}
