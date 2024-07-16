/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:19:00 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/16 12:39:00 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_give_index(int num, char *str)
{
	int	i;
	int	rem;
	int	len;
	int	n;

	ft_printf("nb = %d\n", num);
	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return ;
	}
	rem = 0;
	len = 0;
	n = num;
	while (len++ && n != 0)
		n /= 10;
	i = len - 1;
	while (i >= 0)
	{
		rem = num % 10;
		num = num / 10;
		str[i] = rem + '0';
		i--;
	}
	str[len] = '\0';
}

static void	ft_generate_temp_filename(char *buffer, size_t buffer_size,
	int counter)
{
	char		counter_str[23];
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

static int	ft_create_or_clear_temp_file(t_infos *infos, char *filename)
{
	int	fd;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		ft_quit(infos, "Error: opening/creating file", 2);
	return (fd);
}

void	ft_generate(t_tokenizer *tok, t_infos *infos, char *delimiter)
{
	char	tmp_filename[256];
	int		fd;

	ft_generate_temp_filename(tmp_filename, sizeof(tmp_filename),
		infos->tmpfile_counter);
	fd = ft_create_or_clear_temp_file(infos, tmp_filename);
	write(fd, tok->heredoc_buffer, ft_strlen(tok->heredoc_buffer));
	close(fd);
	ft_add_token(infos, &infos->tokens, TOKEN_HEREDOC_WORD, tmp_filename);
	ft_add_token(infos, &infos->tokens, TOKEN_HEREDOC_DELIMITER, delimiter);
	infos->tmpfile_counter++;
}
