/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:30:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/06 12:32:35 by gmarquis         ###   ########.fr       */
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

static int	ft_check_line(char *line, char *delimiter)
{
	if (!line)
	{
		printf("\nminishell: warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
		return (1);
	}
	if (ft_strncmp(line, delimiter, ft_strlen(line) - 1) == 0)
		return (1);
	return (0);
}

void	ft_heredoc(t_tokenizer *tok, t_infos *infos, char *delimiter)
{
	size_t (heredoc_size) = BUFFER_SIZE;
	size_t	new_size;
	char *line;

	while (1)
	{
		ft_printf("> ");
		line = get_next_line(0, '\n');
		if (ft_check_line(line, delimiter) || g_signal == 0)
		{
			free(line);
			break;
		}
		new_size = ft_strlen(tok->heredoc_buffer) + ft_strlen(line) + 2;
		if (new_size > heredoc_size)
		{
			tok->heredoc_buffer = ft_realloc(tok->heredoc_buffer, ft_strlen(tok->heredoc_buffer), new_size);
			if (!tok->heredoc_buffer)
				ft_quit(infos, "Error: echec malloc heredoc_buffer.\n", 2);
			heredoc_size = new_size;
		}
		ft_strcat(tok->heredoc_buffer, line);
		line = ft_free_str(line);
	}
	ft_generate(infos, tok->heredoc_buffer, delimiter);
}

void	ft_handle_heredoc(t_tokenizer *tok, t_infos *infos)
{
	char	*delimiter;

	tok->heredoc_buffer = malloc(BUFFER_SIZE);
	if (!tok->heredoc_buffer)
		ft_quit(infos, "Error: echec malloc heredoc_buffer.\n", 2);
	tok->heredoc_buffer[0] = '\0';
	delimiter = ft_strdup(tok->buffer);
	g_signal = 1;
	ft_heredoc(tok, infos, delimiter);
	g_signal = 0;
	delimiter = ft_free_str(delimiter);
}
