/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pour_les_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:09:23 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/19 15:38:30 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(t_env *ev)
{
	while (ev)
	{
		ft_printf("%s %s\n\n", ev->name_folder, ev->value_folder);
		ev = ev->next;
	}
}

void	ft_print_tokens(t_token *tokens)
{
	int		i;
	int		count_token;
	t_token	*tmp;

	tmp = tokens;
	count_token = 0;
	while (tmp)
	{
		i = 0;
		ft_printf("Type: %d, ", tmp->type);
		ft_printf("Value: %s", tmp->value[0]);
		while (tmp->value[++i])
			ft_printf(", %s", tmp->value[i]);
		ft_printf("\n");
		count_token++;
		tmp = tmp->NEXT;
	}
	ft_printf("Nombre de tokens: %d\n\n", count_token);
}

//		print surcouche		//

static void	ft_print_files(t_files *files)
{
	while (files)
	{
		if (files->type == TOKEN_REDIRECT_IN)
			ft_printf("  File: %s, Type: IN_FILE\n", files->file);
		else if (files->type == TOKEN_HEREDOC_WORD)
			ft_printf("  File: %s, Type: HEREDOC\n", files->file);
		else if (files->type == TOKEN_REDIRECT_OUT)
			ft_printf("  File: %s, Type: OUT_FILE\n", files->file);
		else if (files->type == TOKEN_REDIRECT_APPEND)
			ft_printf("  File: %s, Type: APPEND\n", files->file);
		files = files->NEXT;
	}
}

static void	ft_print_tok(t_tok *tok)
{
	int	i;

	while (tok)
	{
		ft_printf("Command: ");
		if (tok->cmd)
		{
			i = 0;
			while (tok->cmd[i])
			{
				ft_printf("%s ", tok->cmd[i]);
				i++;
			}
		}
		ft_printf("\nInput files:\n");

		ft_print_files(tok->infile);

		ft_printf("Output files:\n");

		ft_print_files(tok->outfile);
		tok = tok->NEXT;
		if (tok)
			ft_printf("\n--- Next cmd via pipe ---\n\n");
	}
}

void	ft_check_and_print_tok(t_infos *infos)
{
	ft_printf("--- PARSE ---\n");
	if (!infos->tok)
	{
		ft_printf("No commands found.\n");
		return ;
	}
	ft_print_tok(infos->tok);
}
/*
bash --posix
valgrind --suppressions=supp.supp ./minishell
<<0<<1<<2<<3<<4<<5<<6<<7<<8<<9<<10<<11
*/
