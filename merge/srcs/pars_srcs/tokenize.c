/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 02:56:29 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/22 17:30:18 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_handle_quote(t_tokenizer *tok)
{
	if (tok->quote_char)
		tok->quote_char = 0;
	else
		tok->quote_char = tok->input[tok->i];
}

static t_type	ft_get_token_type(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (TOKEN_REDIRECT_IN);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (TOKEN_REDIRECT_OUT);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (TOKEN_REDIRECT_APPEND);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (str[0] == '$')
		return (TOKEN_ENV);
	return (TOKEN_COMMAND);
}

static void	ft_handle_heredoc_operator(t_tokenizer *tok, t_infos *infos)
{
	tok->i++;
	ft_add_token(infos, &infos->tokens, TOKEN_HEREDOC, "<<");
	while (tok->input[tok->i] == ' ' || tok->input[tok->i] == '\f'
		|| tok->input[tok->i] == '\v' || tok->input[tok->i] == '\n'
		|| tok->input[tok->i] == '\t')
		tok->i++;
	if (tok->input[tok->i + 1])
	{
		ft_extract_heredoc_delimiter(tok);
		ft_handle_heredoc(tok, infos);
		ft_clear_heredoc_buffer(tok);
	}
	else
		return ;
}

static void	ft_handle_operator(t_tokenizer *tok, t_infos *infos)
{
	ft_add_token_from_buffer(infos, tok, &tok->j);
	if (tok->input[tok->i] == '>' && tok->input[tok->i + 1] == '>')
	{
		ft_add_token(infos, &infos->tokens, TOKEN_REDIRECT_APPEND, ">>");
		tok->i++;
	}
	else if (tok->input[tok->i] == '<' && tok->input[tok->i + 1] == '<')
		ft_handle_heredoc_operator(tok, infos);
	else
	{
		tok->op[0] = tok->input[tok->i];
		tok->op[1] = '\0';
		ft_add_token(infos, &infos->tokens, ft_get_token_type(tok->op),
			tok->op);
	}
	tok->current_type = TOKEN_COMMAND;
}

void	ft_tokenize(t_infos *infos)
{
	t_tokenizer	tok;

	ft_init_tokenizer(&tok, infos);
	while (tok.input[++tok.i])
	{
		if (tok.j >= tok.buffer_size - 1)
			ft_expand_buffer(infos, &tok);
		if (tok.input[tok.i] == ' ' && !tok.quote_char)
		{
			ft_add_token_from_buffer(infos, &tok, &tok.j);
			tok.current_type = TOKEN_COMMAND;
		}
		else if ((tok.input[tok.i] == '|' || tok.input[tok.i] == '<'
				|| tok.input[tok.i] == '>') && !tok.quote_char)
			ft_handle_operator(&tok, infos);
		else if ((tok.input[tok.i] == '\'' || tok.input[tok.i] == '"')
			&& (!tok.quote_char || tok.quote_char == tok.input[tok.i]))
			ft_handle_quote(&tok);
		else if (tok.input[tok.i] == '$' && tok.quote_char != '\'')
			ft_handle_env_var(&tok, infos);
		else
			tok.buffer[tok.j++] = tok.input[tok.i];
	}
	ft_add_token_from_buffer(infos, &tok, &tok.j);
	tok.buffer = ft_free_str(tok.buffer);
}
