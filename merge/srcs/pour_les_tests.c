/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pour_les_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:09:23 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/26 17:55:15 by gmarquis         ###   ########.fr       */
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
	t_files	*tmp;

	tmp = files;
	while (tmp)
	{
		if (tmp->type == TOKEN_REDIRECT_IN)
			ft_printf("  File_name: %s, Type: IN_FILE\n", tmp->file);
		else if (tmp->type == TOKEN_HEREDOC_WORD)
			ft_printf("  File_name: %s, Type: HEREDOC\n", tmp->file);
		else if (tmp->type == TOKEN_REDIRECT_OUT)
			ft_printf("  File_name: %s, Type: OUT_FILE\n", tmp->file);
		else if (tmp->type == TOKEN_REDIRECT_APPEND)
			ft_printf("  File_name: %s, Type: APPEND\n", tmp->file);
		tmp = tmp->NEXT;
	}
}

static void	ft_print_tok(t_tok *tok)
{
	int	i;
	t_tok	*tmp;

	tmp = tok;
	while (tmp)
	{
		ft_printf("infos->tok->cmd: ");
		if (tmp->cmd)
		{
			i = 0;
			while (tmp->cmd[i])
			{
				ft_printf("%s ", tmp->cmd[i]);
				i++;
			}
		}
		ft_printf("\ninfos->tok->infile:\n");

		ft_print_files(tmp->infile);

		ft_printf("infos->tok->outfile:\n");

		ft_print_files(tmp->outfile);
		tmp = tmp->NEXT;
		if (tmp)
			ft_printf("\n--- Next tok via pipe ---\n\n");
	}
}

void	ft_check_and_print_tok(t_infos *infos)
{
	ft_printf("\n--- PARSE ---\n\n");
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
*/
