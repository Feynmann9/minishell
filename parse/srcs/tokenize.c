/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 02:56:29 by gmarquis          #+#    #+#             */
/*   Updated: 2024/06/16 04:43:58 by gmarquis         ###   ########.fr       */
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

void	ft_handle_heredoc(t_tokenizer *tok, t_infos *infos)
{
	char	*delimiter;
	char	*line;
	size_t	new_size;

	delimiter = ft_strdup(tok->buffer);
	tok->heredoc_buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!tok->heredoc_buffer)
		ft_exit(2, "Error: malloc heredoc_buffer failed\n");
	tok->heredoc_buffer[0] = '\0';
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)		//	a modifier
			break ;
		new_size = ft_strlen(tok->heredoc_buffer) + ft_strlen(line) + 2;
		tok->heredoc_buffer = realloc(tok->heredoc_buffer, new_size);
		if (!tok->heredoc_buffer)
			ft_exit(2, "Error: realloc heredoc_buffer failed\n");
		strcat(tok->heredoc_buffer, line);		//	a modifier
		strcat(tok->heredoc_buffer, "\n");		//	a modifier
		free(line);
	}
	free(line);
	ft_add_token(&infos->tokens, TOKEN_HEREDOC, tok->heredoc_buffer);
	free(delimiter);
	free(tok->heredoc_buffer);
	tok->heredoc_buffer = NULL;
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
		tok->j = 0;
		while (tok->input[++tok->i] && tok->input[tok->i] == ' ')
			;
		while (tok->input[tok->i] && tok->input[tok->i] != ' ')
			tok->buffer[tok->j++] = tok->input[tok->i++];
		tok->buffer[tok->j] = '\0';
		tok->i--;
		ft_handle_heredoc(tok, infos);
	}
	else
	{
		tok->op[0] = tok->input[tok->i];
		tok->op[1] = '\0';
		ft_add_token(&infos->tokens, ft_get_token_type(tok->op), tok->op);
	}
	tok->current_type = TOKEN_COMMAND;
}

void	ft_read_heredoc(t_tokenize_state *state, t_infos *infos,
	char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		while (*line)
		{
			if (state->j >= state->buffer_size - 1)
				ft_resize_buffer(state);
			state->buffer[state->j++] = *line++;
		}
		state->buffer[state->j++] = '\n';
		free(line);
	}
	state->buffer[state->j] = '\0';
	ft_add_token(&infos->tokens, TOKEN_HEREDOC, state->buffer);
	state->j = 0;
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
			tok.buffer[tok.j++] = tok.input[tok.i];
	}
	ft_add_token_from_buffer(infos, &tok, &tok.j);
	free(tok.buffer);
}
