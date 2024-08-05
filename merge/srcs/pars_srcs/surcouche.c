/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surcouche.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:40:38 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/05 08:20:36 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//		init/add		//

static void	ft_add_cmd(t_infos *infos, t_tok *current_tok, char *cmd)
{
	char	**new_cmds;
	char	**old_cmds;

	int (count) = 0;
	int (i) = 0;
	old_cmds = current_tok->cmd;
	if (old_cmds)
	{
		while (old_cmds[count])
			count++;
	}
	new_cmds = malloc(sizeof(char *) * (count + 2));
	if (!new_cmds)
		ft_quit(infos, "Error: echec malloc new_cmds.\n", 2);
	while (i < count)
	{
		new_cmds[i] = old_cmds[i];
		i++;
	}
	new_cmds[count] = ft_strdup(cmd);
	if(!new_cmds[count])
		ft_quit(infos, "Error: echec malloc new_cmds[count].\n", 2);
	new_cmds[count + 1] = NULL;
	free(current_tok->cmd);
	current_tok->cmd = new_cmds;
}

static void	ft_add_utils(t_files *tmp, t_files **file_list, t_files *new_file)
{
	tmp = *file_list;
	while (tmp->NEXT)
		tmp = tmp->NEXT;
	tmp->NEXT = new_file;
}

static t_files	*ft_init_file(t_infos *infos, int type, char *file)
{
	t_files *new;

	new = malloc(sizeof(t_files));
	if (!new)
		ft_quit(infos, "Error: echec malloc new.\n", 2);
	new->type = type;
	new->file = ft_strdup(file);
	if (!new->file)
		ft_quit(infos, "Error: echec malloc new->file.\n", 2);
	new->NEXT = NULL;
	return (new);
}

static void	ft_add_file(t_infos *infos, t_tok *current_tok, int type, char *file)
{
	t_files *(new_file) = NULL;
	t_files **(file_list) = NULL;
	t_files *(tmp) = NULL;
	if (!current_tok)
	{
		current_tok = ft_init_tok(infos);
		ft_add_cmd(infos, current_tok, NULL);
	}
	new_file = ft_init_file(infos, type, file);
	if (type == TOKEN_REDIRECT_IN || type == TOKEN_HEREDOC_WORD)
		file_list = &current_tok->infile;
	else if (type == TOKEN_REDIRECT_OUT || type == TOKEN_REDIRECT_APPEND)
		file_list = &current_tok->outfile;
	else
		return ;
	if (*file_list == NULL)
		*file_list = new_file;
	else
		ft_add_utils(tmp, file_list, new_file);
}

//		code principal		//

static void	ft_surcouche_util(t_infos *infos, t_token *tokens, t_tok *current_tok, int tmp_type)
{
	tmp_type = tokens->type;
	tokens = tokens->NEXT;
	if (tmp_type == TOKEN_REDIRECT_IN
		&& tokens->type == TOKEN_COMMAND)
		ft_add_file(infos, current_tok, TOKEN_REDIRECT_IN,
			tokens->value[0]);
	else if (tmp_type == TOKEN_HEREDOC
		&& tokens->type == TOKEN_HEREDOC_WORD)
		ft_add_file(infos, current_tok, TOKEN_HEREDOC_WORD,
			tokens->value[0]);
	else if (tmp_type == TOKEN_REDIRECT_OUT
		&& tokens->type == TOKEN_COMMAND)
		ft_add_file(infos, current_tok, TOKEN_REDIRECT_OUT,
			tokens->value[0]);
	else if (tmp_type == TOKEN_REDIRECT_APPEND
		&& tokens->type == TOKEN_COMMAND)
		ft_add_file(infos, current_tok, TOKEN_REDIRECT_APPEND,
			tokens->value[0]);
	tmp_type = 0;
}

static void	ft_make_current_tok(t_infos *infos, t_tok **current_tok, t_tok **head)
{
	t_tok	*temp;

	*current_tok = ft_init_tok(infos);
	if (!*head)
		*head = *current_tok;
	else
	{
		temp = *head;
		while (temp->NEXT)
			temp = temp->NEXT;
		temp->NEXT = *current_tok;
	}
}

void	ft_surcouche(t_infos *infos)
{
	t_token *tokens = infos->tokens;
	t_tok *head = NULL;
	t_tok *current_tok = NULL;
	int (tmp_type) = 0;
	while (tokens)
	{
		if (!current_tok)
			ft_make_current_tok(infos, &current_tok, &head);
		if (tokens->type == TOKEN_COMMAND || tokens->type == TOKEN_ENV)
			ft_add_cmd(infos, current_tok, tokens->value[0]);
		else if (tokens->type == TOKEN_REDIRECT_IN
			|| tokens->type == TOKEN_HEREDOC)
			{
				if (tokens->NEXT)
					ft_surcouche_util(infos, tokens, current_tok, tmp_type);
				else
					infos->error = "bash: syntax error near unexpected token `newline'";
				if (tokens->NEXT)
					tokens = tokens->NEXT;
			}
		else if (tokens->type == TOKEN_REDIRECT_OUT
			|| tokens->type == TOKEN_REDIRECT_APPEND)
			{
				if (tokens->NEXT)
					ft_surcouche_util(infos, tokens, current_tok, tmp_type);
				else
					infos->error = "bash: syntax error near unexpected token `newline'";
				if (tokens->NEXT)
					tokens = tokens->NEXT;
			}
		else if (tokens->type == TOKEN_PIPE)
		{
			current_tok = NULL;
			infos->count_pipes++;
		}
		tokens = tokens->NEXT;
	}
	infos->tok = head;
}
