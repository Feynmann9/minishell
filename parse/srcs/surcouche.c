/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surcouche.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:40:38 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/12 13:46:25 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

//		free tok		//

void ft_free_files(t_files *files)
{
	t_files *temp;

	while (files)
	{
		temp = files;
		files = files->NEXT;
		temp->file = ft_free_str(temp->file);
		free(temp);
	}
}

void ft_free_tok(t_tok *tok)
{
	t_tok	*temp;
	int		i;

	while (tok)
	{
		temp = tok;
		if (tok->cmd)
		{
			i = 0;
			while (tok->cmd[i])
			{
				free(tok->cmd[i]);
				i++;
			}
			free(tok->cmd);
		}
		ft_free_files(tok->infile);
		ft_free_files(tok->outfile);
		tok = tok->NEXT;
		free(temp);
	}
}

//		print tok		//

void ft_print_files(t_files *files)
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

void ft_print_tok(t_tok *tok)
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
		ft_printf("\n");
		ft_printf("Input files:\n");
		ft_print_files(tok->infile);
		ft_printf("Output files:\n");
		ft_print_files(tok->outfile);
		tok = tok->NEXT;
		if (tok)
			ft_printf("\n--- Next Command ---\n\n");
	}
}

void ft_check_and_print_tok(t_infos *infos)
{
	ft_printf("PRINT:\n");
	if (!infos->tok)
	{
		ft_printf("No commands found.\n");
		return ;
	}
	ft_print_tok(infos->tok);
}

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

void ft_add_file(t_files **file_list, int type, char *file)
{
	t_files *new_file;
	new_file = malloc(sizeof(t_files));
	if (!new_file)
		return ;
	new_file->type = type;
	new_file->file = ft_strdup(file);
	new_file->NEXT = *file_list;
	*file_list = new_file;
}

void ft_add_cmd(t_tok *current_tok, char *cmd)
{
	int count = 0;
	int i = 0;
	char **new_cmds;
	char **old_cmds = current_tok->cmd;

	if (old_cmds)
	{
		while (old_cmds[count])
		{
			count++;
		}
	}
	new_cmds = malloc(sizeof(char *) * (count + 2));
	if (!new_cmds)
		return;

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

//		code principal		//

void	ft_surcouche(t_infos *infos)
{
	t_token *tokens = infos->tokens;
	t_tok *head = NULL;
	t_tok *current_tok = NULL;
	t_tok *temp = NULL;
	int	tmp_type = 0;

	ft_print_tokens(infos->tokens);
	ft_printf("SURCOUCHE:\n");
	while (tokens)
	{
		ft_printf("ici\n");		//	test en cours, degfault avec "< out bla"
		if (tokens->type == TOKEN_COMMAND || tokens->type == TOKEN_ENV)
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
			ft_add_cmd(current_tok, tokens->value[0]);
		}
		else if (tokens->type == TOKEN_REDIRECT_IN || tokens->type == TOKEN_HEREDOC)
		{
			if (tokens->NEXT != NULL)
			{
				tokens = tokens->NEXT;
				if (tokens->type == TOKEN_COMMAND)
					ft_add_file(&current_tok->infile, TOKEN_REDIRECT_IN, tokens->value[0]);
				else if (tokens->type == TOKEN_HEREDOC_WORD)
					ft_add_file(&current_tok->infile, TOKEN_HEREDOC_WORD, tokens->value[0]);
			}
		}
		else if (tokens->type == TOKEN_REDIRECT_OUT || tokens->type == TOKEN_REDIRECT_APPEND)
		{
			if (tokens->NEXT != NULL)
			{
				tmp_type = tokens->type;
				tokens = tokens->NEXT;
				if (tmp_type == TOKEN_REDIRECT_OUT && tokens->type == TOKEN_COMMAND)
					ft_add_file(&current_tok->outfile, TOKEN_REDIRECT_OUT, tokens->value[0]);
				else if (tmp_type == TOKEN_REDIRECT_APPEND && tokens->type == TOKEN_COMMAND)
					ft_add_file(&current_tok->outfile, TOKEN_REDIRECT_APPEND, tokens->value[0]);
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
	ft_free_tok(infos->tok);
	ft_free_tokens(&infos->tokens);
}
