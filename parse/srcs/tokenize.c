/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 02:56:29 by gmarquis          #+#    #+#             */
/*   Updated: 2024/06/16 23:58:54 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

t_type	ft_get_token_type(char *str)
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

void	ft_handle_heredoc(t_tokenizer *tok, t_infos *infos)
{
	char	*delimiter;
	char	*line;
	size_t	heredoc_size;
	size_t	new_size;

	delimiter = ft_strdup(tok->buffer);
	tok->heredoc_buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!tok->heredoc_buffer)
		ft_exit(2, "Error: malloc heredoc_buffer failed\n");
	tok->heredoc_buffer[0] = '\0';
	heredoc_size = BUFFER_SIZE;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		new_size = ft_strlen(tok->heredoc_buffer) + ft_strlen(line) + 2;
		if (new_size > heredoc_size) {
			tok->heredoc_buffer = ft_realloc(tok->heredoc_buffer, heredoc_size, new_size);
			if (!tok->heredoc_buffer)
				ft_exit(2, "Error: realloc heredoc_buffer failed\n");
			heredoc_size = new_size;
		}
		ft_strcat(tok->heredoc_buffer, line);
		ft_strcat(tok->heredoc_buffer, "\n");
		free(line);
	}
	ft_add_token(&infos->tokens, TOKEN_HEREDOC_WORD, tok->heredoc_buffer);
	ft_add_token(&infos->tokens, TOKEN_HEREDOC_DELIMITER, delimiter);
	free(delimiter);
	free(tok->heredoc_buffer);
	tok->heredoc_buffer = NULL;
}

void	ft_handle_operator(t_tokenizer *tok, t_infos *infos)
{
	int		i;

	i = 0;
	ft_add_token_from_buffer(infos, tok, &tok->j);
	if (tok->input[tok->i] == '>' && tok->input[tok->i + 1] == '>')
	{
		ft_add_token(&infos->tokens, TOKEN_REDIRECT_APPEND, ">>");
		tok->i++;
	}
	else if (tok->input[tok->i] == '<' && tok->input[tok->i + 1] == '<')
	{
		tok->i++;
		ft_add_token(&infos->tokens, TOKEN_HEREDOC, "<<");
		while (tok->input[++tok->i] == ' ')
			;
		tok->j = 0;
		while (tok->input[tok->i] && tok->input[tok->i] != ' ')
			tok->buffer[tok->j++] = tok->input[tok->i++];
		tok->buffer[tok->j] = '\0';
		tok->i--;
		ft_handle_heredoc(tok, infos);
		tok->i -= ft_strlen(tok->buffer);
		while (tok->i < (int)(tok->i + ft_strlen(tok->buffer)))
		{
			tok->buffer[i] = '\0';
			tok->i++;
			i++;
		}
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
		if (!line || ft_strcmp(line, delimiter) == 0)
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
