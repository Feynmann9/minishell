/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:30:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/05 16:51:29 by gmarquis         ###   ########.fr       */
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

void	ft_generate_here(char *heredoc_buffer, char *filename)
{
	int		fd;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	write(fd, heredoc_buffer, ft_strlen(heredoc_buffer));
	close(fd);
}

void	heredoc_child_process(t_infos *infos, char *delimiter, char *filename)
{
	size_t (heredoc_size) = BUFFER_SIZE;
	size_t	new_size;
	char *line;
	char *heredoc_buffer = malloc(BUFFER_SIZE);
	if (!heredoc_buffer)
		ft_quit(infos, "Error: echec malloc heredoc_buffer.\n", 2);
	heredoc_buffer[0] = '\0';
	signal(SIGINT, ft_heredoc_signal);

	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		new_size = ft_strlen(heredoc_buffer) + ft_strlen(line) + 2;
		if (new_size > heredoc_size)
		{
			heredoc_buffer = ft_realloc(heredoc_buffer, ft_strlen(heredoc_buffer), new_size);
			if (!heredoc_buffer)
				ft_quit(infos, "Error: echec malloc heredoc_buffer.\n", 2);
			heredoc_size = new_size;
		}
		ft_strcat(heredoc_buffer, line);
		ft_strcat(heredoc_buffer, "\n");
		line = ft_free_str(line);
	}
	ft_generate_here(heredoc_buffer, filename);
	exit(0);
}

void heredoc(t_infos *infos, char *delimiter, char *filename)
{
	pid_t pid = fork();
	int status;

	if (pid == 0)
		heredoc_child_process(infos, delimiter, filename);
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork");
}

void	ft_handle_heredoc(t_tokenizer *tok, t_infos *infos)
{
	char	*delimiter;
	char	tmp_filename[260];

	ft_generate_temp_filename(tmp_filename, sizeof(tmp_filename),
		infos->tmpfile_counter);
	delimiter = ft_strdup(tok->buffer);
	g_signal = 1;
	heredoc(infos, delimiter, tmp_filename);
	delimiter = ft_free_str(delimiter);
	if (g_signal == 1)
	{
		ft_add_token(infos, &infos->tokens, TOKEN_HEREDOC_WORD, tmp_filename);
		ft_add_token(infos, &infos->tokens, TOKEN_HEREDOC_DELIMITER, delimiter);
		if (infos->tmpfile_counter == 256)
			infos->tmpfile_counter = 0;
		else
			infos->tmpfile_counter++;
		g_signal = 0;
	}
}
