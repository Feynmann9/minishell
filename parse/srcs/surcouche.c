/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surcouche.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:40:38 by gmarquis          #+#    #+#             */
/*   Updated: 2024/06/15 05:28:36 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void ft_add_command(t_list **commands, t_command *command)
{
    t_lists *new_node;

    new_node = ft_lstnew(command);
    if (!new_node)
        ft_exit(1, "Error: malloc failed\n");
    ft_lstadd_back(commands, new_node);
}

void ft_free_commands(t_list **commands)
{
    t_lists *temp;
    t_command *command;

    while (*commands)
    {
        temp = *commands;
        *commands = (*commands)->next;
        command = (t_command *)temp->content;
        if (command->args)
            free(command->args);
        free(command);
        free(temp);
    }
}

void ft_print_commands(t_list *commands)
{
    t_command *command;
    int i;

    while (commands)
    {
        command = (t_command *)commands->content;
        printf("Command:\n");

        i = 0;
        while (i < command->args_count)
        {
            printf("  Arg[%d]: %s\n", i, command->args[i]);
            i++;
        }

        if (command->input_file)
            printf("  Input: %s\n", command->input_file);
        if (command->output_file)
            printf("  Output: %s\n", command->output_file);
        if (command->append_file)
            printf("  Append: %s\n", command->append_file);
        if (command->heredoc_delim)
            printf("  Heredoc: %s\n", command->heredoc_delim);

        printf("\n");
        commands = commands->next;
    }
}

void ft_surcouche(t_infos *infos)
{
    t_lists *commands = NULL;
    t_command *current_command = NULL;
    t_lists *tokens_list = infos->tokens;
    t_token *token;

    while (tokens_list)
    {
        token = (t_token *)tokens_list->content;
        if (!current_command)
        {
            current_command = malloc(sizeof(t_command));
            if (!current_command)
                ft_exit(1, "Error: malloc failed\n");
            ft_bzero(current_command, sizeof(t_command));
        }

        if (token->type == TOKEN_COMMAND)
        {
            if (!current_command->args)
            {
                current_command->args = malloc(sizeof(char *) * 10); // Taille initiale arbitraire
                if (!current_command->args)
                    ft_exit(1, "Error: malloc failed\n");
                current_command->args_count = 0;
            }
            current_command->args[current_command->args_count++] = token->value;
        }
        else if (token->type == TOKEN_REDIRECT_IN)
            current_command->input_file = token->value;
        else if (token->type == TOKEN_REDIRECT_OUT)
            current_command->output_file = token->value;
        else if (token->type == TOKEN_REDIRECT_APPEND)
            current_command->append_file = token->value;
        else if (token->type == TOKEN_HEREDOC)
            current_command->heredoc_delim = token->value;
        else if (token->type == TOKEN_PIPE)
        {
            ft_add_command(&commands, current_command);
            current_command = NULL;
        }

        tokens_list = tokens_list->next;
    }

    if (current_command)
        ft_add_command(&commands, current_command);

	ft_free_tokens(&infos->tokens);
	ft_print_commands(commands);
	ft_free_commands(&commands);
}
