/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surcouche.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:40:38 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/16 15:00:36 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//		init/add		//

t_tok	*ft_init_tok()
{
	t_tok *new_tok;

	new_tok = malloc(sizeof(t_tok));
	if (!new_tok)
		ft_exit(2, "Error: echec malloc new_tok.\n;");
	new_tok->cmd = NULL;
	new_tok->infile = NULL;
	new_tok->outfile = NULL;
	new_tok->NEXT = NULL;
	return (new_tok);
}

void ft_add_cmd(t_tok *current_tok, char *cmd)
{
	int count = 0;
	int i = 0;
	char **new_cmds;
	char **old_cmds;

	old_cmds = current_tok->cmd;
	if (old_cmds)
	{
		while (old_cmds[count])
			count++;
	}
	new_cmds = malloc(sizeof(char *) * (count + 2));
	if (!new_cmds)
		return ;
	while (i < count)
	{
		new_cmds[i] = old_cmds[i];
		i++;
	}
	new_cmds[count] = ft_strdup(cmd);
	new_cmds[count + 1] = NULL;
	free(current_tok->cmd);
	current_tok->cmd = new_cmds;
}
void ft_add_file(t_tok *current_tok, int type, char *file)
{
	t_files *new_file;
	t_files **file_list;
	t_files *tmp;

	if (!current_tok)
	{
		current_tok = ft_init_tok();
		ft_add_cmd(current_tok, NULL);
	}
	new_file = malloc(sizeof(t_files));
	if (!new_file)
		return ;
	new_file->type = type;
	new_file->file = ft_strdup(file);
	new_file->NEXT = NULL;
	if (type == TOKEN_REDIRECT_IN || type == TOKEN_HEREDOC_WORD)
		file_list = &current_tok->infile;
	else if (type == TOKEN_REDIRECT_OUT || type == TOKEN_REDIRECT_APPEND)
		file_list = &current_tok->outfile;
	else
		return ;
	if (*file_list == NULL)
		*file_list = new_file;
	else
	{
		tmp = *file_list;
		while (tmp->NEXT)
			tmp = tmp->NEXT;
		tmp->NEXT = new_file;
	}
}

//		code principal		//

void	ft_surcouche(t_infos *infos)
{
	t_token *tokens = infos->tokens;
	t_tok *head = NULL;
	t_tok *current_tok = NULL;
	t_tok *temp = NULL;
	int	tmp_type = 0;

	//ft_print_tokens(infos->tokens);
	//ft_printf("/--SURCOUCHE--\\\n");
	while (tokens)
	{
		if (!current_tok)
		{
			current_tok = ft_init_tok();
			if (!head)
				head = current_tok;
			else
			{
				temp = head;
				while (temp->NEXT)
					temp = temp->NEXT;
				temp->NEXT = current_tok;
			}
		}
		if (tokens->type == TOKEN_COMMAND || tokens->type == TOKEN_ENV)
			ft_add_cmd(current_tok, tokens->value[0]);
		else if (tokens->type == TOKEN_REDIRECT_IN || tokens->type == TOKEN_HEREDOC)
		{
			if (tokens->NEXT != NULL)
			{
				tmp_type = tokens->type;
				tokens = tokens->NEXT;
				if (tmp_type == TOKEN_REDIRECT_IN && tokens->type == TOKEN_COMMAND)
					ft_add_file(current_tok, TOKEN_REDIRECT_IN, tokens->value[0]);
				else if (tmp_type == TOKEN_HEREDOC && tokens->type == TOKEN_HEREDOC_WORD)
					ft_add_file(current_tok, TOKEN_HEREDOC_WORD, tokens->value[0]);
				tmp_type = 0;
			}
		}
		else if (tokens->type == TOKEN_REDIRECT_OUT || tokens->type == TOKEN_REDIRECT_APPEND)
		{
			if (tokens->NEXT != NULL)
			{
				tmp_type = tokens->type;
				tokens = tokens->NEXT;
				if (tmp_type == TOKEN_REDIRECT_OUT && tokens->type == TOKEN_COMMAND)
					ft_add_file(current_tok, TOKEN_REDIRECT_OUT, tokens->value[0]);
				else if (tmp_type == TOKEN_REDIRECT_APPEND && tokens->type == TOKEN_COMMAND)
					ft_add_file(current_tok, TOKEN_REDIRECT_APPEND, tokens->value[0]);
				tmp_type = 0;
			}
		}
		else if (tokens->type == TOKEN_PIPE)
		{
			current_tok = NULL;
			infos->count_pipes++;
		}
		tokens = tokens->NEXT;
	}
	infos->tok = head;
	ft_check_and_print_tok(infos);
	//ft_free_tok(infos->tok);
	ft_free_tokens(&infos->tokens);
}
