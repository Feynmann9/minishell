/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 04:57:49 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/06 12:18:19 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static char	*ft_alt_strjoin(char *s1, char *s2)
{
	size_t	i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen(s2);
	if (!s1)
		return (ft_strndup(s2, len));
	len = len + ft_strlen(s1);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	len = 0;
	while (s1[i])
		str[len++] = s1[i++];
	i = 0;
	while (s2[i])
		str[len++] = s2[i++];
	str[len] = '\0';
	ft_free_str(s1);
	return (str);
}

static char	*print_line(char **tempo)
{
	int		i;
	char	*line;
	char	*str;

	if (!*tempo)
		return (NULL);
	str = *tempo;
	i = 0;
	while (str[i] && str[i] != 10)
		i++;
	if (str[i] == 10)
		i++;
	line = ft_strndup(str, i);
	*tempo = ft_strndup(str + i, ft_strlen(str + i));
	str = ft_free_str(str);
	return (line);
}

static int	ft_verif_n(char n)
{
	if (n == '\0' || !n)
		return (0);
	return (1);
}

char	*get_next_line(int fd, char n)
{
	static char	*tempo[1024];
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (tempo[fd] = ft_free_str(tempo[fd]), NULL);
	if (!ft_verif_n(n))
		n = '\n';
	if (ft_contain_n(tempo[fd], n))
		return (print_line(&tempo[fd]));
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = 0;
		tempo[fd] = ft_alt_strjoin(tempo[fd], buffer);
		if (ft_contain_n(tempo[fd], n))
			break ;
	}
	if (buffer)
		buffer = ft_free_str(buffer);
	return (print_line(&tempo[fd]));
}
