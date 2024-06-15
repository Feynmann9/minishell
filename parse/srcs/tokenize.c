/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 02:56:29 by gmarquis          #+#    #+#             */
/*   Updated: 2024/06/15 03:15:40 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

t_type	ft_get_token_type(char *str)
{
	if (strcmp(str, "|") == 0)
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

void	ft_handle_operator(t_tokenizer *tok, t_infos *infos)
{
	ft_add_token_from_buffer(infos, tok, &tok->j);
	if (tok->input[tok->i] == '>' && tok->input[tok->i + 1] == '>')
	{
		ft_add_token(&infos->tokens, TOKEN_REDIRECT_APPEND, ">>");
		tok->i++;
	}
	else if (tok->input[tok->i] == '<' && tok->input[tok->i + 1] == '<')
	{
		ft_add_token(&infos->tokens, TOKEN_HEREDOC, "<<");
		tok->i++;
	}
	else
	{
		tok->op[0] = tok->input[tok->i];
		tok->op[1] = '\0';
		ft_add_token(&infos->tokens, ft_get_token_type(tok->op), tok->op);
	}
	tok->current_type = TOKEN_COMMAND;
}

void	ft_process_char(t_tokenizer *tok)
{
	tok->buffer[tok->j++] = tok->input[tok->i];
}

void	ft_tokenize(t_infos *infos)
{
	t_tokenizer	tok;

	ft_init_tokenizer(&tok, infos);
	while (tok.input[++tok.i])
	{
		if (tok.j >= tok.buffer_size - 1)
			ft_expand_buffer(&tok);
		if (tok.input[tok.i] == ' ' && !tok.quote_char)
		{
			ft_add_token_from_buffer(infos, &tok, &tok.j);
			tok.current_type = TOKEN_COMMAND;
		}
		else if (tok.input[tok.i] == '|' || tok.input[tok.i] == '<'
			|| tok.input[tok.i] == '>')
			ft_handle_operator(&tok, infos);
		else if ((tok.input[tok.i] == '\'' || tok.input[tok.i] == '"')
			&& (!tok.quote_char || tok.quote_char == tok.input[tok.i]))
			ft_handle_quote(&tok);
		else if (tok.input[tok.i] == '$' && tok.quote_char != '\'')
			ft_handle_env_var(&tok, infos);
		else
			ft_process_char(&tok);
	}
	ft_add_token_from_buffer(infos, &tok, &tok.j);
	free(tok.buffer);
}
