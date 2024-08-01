/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:30:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/01 23:23:17 by gmarquis         ###   ########.fr       */
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
		&& tok->input[tok->i] != '<' && tok->input[tok->i] != '>'
		&& tok->input[tok->i] != '|')
		tok->buffer[tok->j++] = tok->input[tok->i++];
	tok->buffer[tok->j] = '\0';
	tok->i--;
}

void	ft_collect_heredoc_lines(t_tokenizer *tok, char *delimiter, t_infos *infos)
{
	char	*line;
	size_t (heredoc_size) = BUFFER_SIZE;
	size_t	new_size;

	g_signal = 1;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			line = ft_free_str(line);
			break;
		}
		new_size = ft_strlen(tok->heredoc_buffer) + ft_strlen(line) + 2;
		if (new_size > heredoc_size)
		{
			tok->heredoc_buffer = realloc(tok->heredoc_buffer, new_size);
			if (!tok->heredoc_buffer)
				ft_quit(infos, "Error: echec malloc heredoc_buffer.\n", 2);
			heredoc_size = new_size;
		}
		ft_strcat(tok->heredoc_buffer, line);
		ft_strcat(tok->heredoc_buffer, "\n");
		line = ft_free_str(line);
	}
	g_signal = 0;
}

void	ft_handle_heredoc(t_tokenizer *tok, t_infos *infos)
{
	char	*delimiter;

	delimiter = ft_strdup(tok->buffer);
	tok->heredoc_buffer = malloc(BUFFER_SIZE);
	if (!tok->heredoc_buffer)
		ft_quit(infos, "Error: echec malloc heredoc_buffer.\n", 2);
	tok->heredoc_buffer[0] = '\0';
	g_signal = 1;
	ft_collect_heredoc_lines(tok, delimiter, infos);
	g_signal = 0;
	if (tok->heredoc_buffer)
		ft_generate(tok, infos, delimiter);
	delimiter = ft_free_str(delimiter);
	tok->heredoc_buffer = ft_free_str(tok->heredoc_buffer);
}
