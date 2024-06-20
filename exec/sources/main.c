/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matran-d <matran-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:39:09 by gmarquis          #+#    #+#             */
/*   Updated: 2024/06/20 15:35:40 by matran-d         ###   ########.fr       */
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
	char new_1[5000];
	char new_2[5000];

    tmp = env;
    while (*tmp)
    {
		ft_split_env(*tmp, new_1, new_2);
        new_env(ev, new_1, new_2);
        tmp++;
    }
}

void	ft_split_env(char *tmp, char *new_1, char *new_2)
{
	int i = 0;
	int j = 0;

	while (tmp[i])
	{
		//printf("%s\n", tmp);
		while (tmp[i] != '=')
		{
			new_1[j] = tmp[i];
			i++;
			j++;
		}
		while (new_1[j])
			new_1[j++] = '\0';
		//printf("new_1 = %s\n", new_1);
		j = 0;
		i++;
		while (tmp[i] != '\0')
		{
			new_2[j] = tmp[i];
			i++;
			j++;
		}
		while (new_2[j])
			new_2[j++] = '\0';
		//printf("new_2 = %s\n", new_2);
		//free(new_1);
		//free(new_2);
	}
}

void split_input(char *input, t_cmd *command)
{
    int arg_count = 0;
    char *token;

    token = strtok(input, " ");
    command->cmd = strdup(token);

    while (token != NULL)
    {
        command->args = realloc(command->args, sizeof(char *) * (arg_count + 1));
        command->args[arg_count] = strdup(token);
        token = strtok(NULL, " ");
        arg_count++;
    }
    command->args = realloc(command->args, sizeof(char *) * (arg_count + 1));
    command->args[arg_count] = NULL;
}


int main(int argc, char **argv, char **env)
{
    t_env *ev = NULL;
    t_base *base = NULL;
    char *input;

    if (argc > 3 || argv == NULL)
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
        split_input(input, base->command);
        builtin(base, env);
        free(input);
    }
    return (0);
}
