/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:19:00 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/06 11:24:36 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_give_index(int n, char *str)
{
	if (n > 99)
	{
		str[3] = '\0';
		str[2] = n % 10 + '0';
		n /= 10;
		str[1] = n + '0';
		n /= 10;
		str[0] = n + '0';
	}
	else if (n > 9)
	{
		str[2] = '\0';
		str[1] = n % 10 + '0';
		n /= 10;
		str[0] = n + '0';
	}
	else
	{
		str[0] = n + '0';
		str[1] = '\0';
	}
}

void	ft_generate_temp_filename(char *buffer, size_t buffer_size,
	int counter)
{
	char		counter_str[4];
	const char	*prefix = "minishell_tmpfile_";
	size_t		prefix_len;
	size_t		counter_len;

	prefix_len = ft_strlen(prefix);
	if (prefix_len >= buffer_size)
		return ;
	ft_strlcpy(buffer, prefix, buffer_size);
	ft_give_index(counter, counter_str);
	counter_len = ft_strlen(counter_str);
	if (prefix_len + counter_len + 1 >= buffer_size)
		return ;
	ft_strlcpy(buffer + prefix_len, counter_str, buffer_size - prefix_len);
}

void	ft_generate(t_infos *infos, char *heredoc_buffer, char *delimiter)
{
	int		fd;
	char	tmp_filename[260];

	ft_generate_temp_filename(tmp_filename, sizeof(tmp_filename),
		infos->tmpfile_counter);
	fd = open(tmp_filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(fd == -1)
		ft_quit(infos, "Error: echec open fd.\n", 2);
	write(fd, heredoc_buffer, ft_strlen(heredoc_buffer));
	close(fd);
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
