/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:30:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/16 12:38:50 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_clear_heredoc_buffer(t_tokenizer *tok)
{
	int	i;

	i = 0;
	tok->i -= ft_strlen(tok->buffer);
	while (i < (int)ft_strlen(tok->buffer))
	{
		tok->buffer[i] = '\0';
		tok->i++;
		i++;
	}
}

void	ft_extract_heredoc_delimiter(t_tokenizer *tok)
{
	tok->j = 0;
	while (tok->input[tok->i] == '<' || tok->input[tok->i] == ' ')
		tok->i++;
	while (tok->input[tok->i] && tok->input[tok->i] != ' '
		&& tok->input[tok->i] != '<' && tok->input[tok->i] != '>' && tok->input[tok->i] != '|')
		tok->buffer[tok->j++] = tok->input[tok->i++];
	tok->buffer[tok->j] = '\0';
	tok->i--;
}

void	ft_collect_heredoc_lines(t_tokenizer *tok, char *delimiter,
	t_infos *infos)
{
	char	*line;
	size_t	heredoc_size;
	size_t	new_size;

	heredoc_size = BUFFER_SIZE;
	line = readline("> ");
	if (!line || ft_strcmp(line, delimiter) == 0)
	{
		line = ft_free_str(line);
		return ;
	}
	new_size = ft_strlen(tok->heredoc_buffer) + ft_strlen(line) + 2;
	if (new_size > heredoc_size)
	{
		tok->heredoc_buffer = ft_realloc(tok->heredoc_buffer, heredoc_size,
				new_size);
		if (!tok->heredoc_buffer)
			ft_quit(infos, "Error: realloc heredoc_buffer failed\n", 2);
		heredoc_size = new_size;
	}
	ft_strcat(tok->heredoc_buffer, line);
	ft_strcat(tok->heredoc_buffer, "\n");
	line = ft_free_str(line);
	ft_collect_heredoc_lines(tok, delimiter, infos);
}

void	ft_handle_heredoc(t_tokenizer *tok, t_infos *infos)
{
	char	*delimiter;

	delimiter = ft_strdup(tok->buffer);
	tok->heredoc_buffer = malloc(BUFFER_SIZE);
	if (!tok->heredoc_buffer)
		ft_quit(infos, "Error: malloc heredoc_buffer failed\n", 2);
	tok->heredoc_buffer[0] = '\0';
	ft_collect_heredoc_lines(tok, delimiter, infos);
	ft_generate(tok, infos, delimiter);
	delimiter = ft_free_str(delimiter);
	tok->heredoc_buffer = ft_free_str(tok->heredoc_buffer);
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
			line = ft_free_str(line);
			break ;
		}
		while (*line)
		{
			if (state->j >= state->buffer_size - 1)
				ft_resize_buffer(infos, state);
			state->buffer[state->j++] = *line++;
		}
		state->buffer[state->j++] = '\n';
		line = ft_free_str(line);
	}
	state->buffer[state->j] = '\0';
	ft_add_token(infos, &infos->tokens, TOKEN_HEREDOC, state->buffer);
	state->j = 0;
}
