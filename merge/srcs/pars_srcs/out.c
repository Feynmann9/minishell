/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:14:56 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/17 18:10:39 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_free_files(t_files *files)
{
	t_files	*tmp;

	while (files != NULL)
	{
		tmp = files;
		files = files->NEXT;
		tmp->file = ft_free_str(tmp->file);
		free(tmp);
		tmp = NULL;
	}
}

void	ft_free_tok(t_tok *tok)
{
	t_tok	*tmp;

	while (tok)
	{
		tmp = tok;
		if (tok->cmd)
			tok->cmd = ft_free_tab2d(tok->cmd);
		if (tok->infile)
			ft_free_files(tok->infile);
		if (tok->outfile)
			ft_free_files(tok->outfile);
		tok = tok->NEXT;
		free(tmp);
	}
}

static void	ft_free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*swap;

	tmp = *env;
	while (tmp)
	{
		swap = tmp->next;
		tmp->name_folder = ft_free_str(tmp->name_folder);
		tmp->value_folder = ft_free_str(tmp->value_folder);
		free(tmp);
		tmp = swap;
	}
	*env = NULL;
}

void	ft_free_tokens(t_token **tokens)
{
	t_token	*tmp;
	t_token	*swap;

	tmp = *tokens;
	while (tmp)
	{
		swap = tmp->NEXT;
		tmp->value = ft_free_tab2d(tmp->value);
		free(tmp);
		tmp = swap;
	}
	*tokens = NULL;
}

void	ft_quit(t_infos *infos, char *message, int out)
{
	ft_free_tokens(&(infos->tokens));
	ft_free_env(&(infos->tmp_env));
	ft_free_tok(infos->tok);
	ft_exit(out, message);
}
