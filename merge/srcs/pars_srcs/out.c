/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:14:56 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/18 15:06:20 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_files	*ft_free_files(t_files *files)
{
	t_files	*tmp;

	while (files)
	{
		tmp = files;
		files = files->NEXT;
		tmp->file = ft_free_str(tmp->file);
		free(tmp);
		tmp = NULL;
	}
	return (NULL);
}

void	ft_free_tok(t_tok **tok)
{
	t_tok	*tmp;
	t_tok	*swap;

	tmp = *tok;
	while (tmp)
	{
		swap = tmp;
		if (tmp->cmd)
			tmp->cmd = ft_free_tab2d(tmp->cmd);
		if (tmp->infile)
			tmp->infile = ft_free_files(tmp->infile);
		if (tmp->outfile)
			tmp->outfile = ft_free_files(tmp->outfile);
		tmp = tmp->NEXT;
		free(swap);
		swap = NULL;
	}
	*tok = NULL;
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
	ft_free_tok(&(infos->tok));
	ft_exit(out, message);
}
