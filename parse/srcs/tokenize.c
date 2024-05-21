/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 02:56:29 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/21 19:24:03 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

t_token	*ft_tokenize(char *input)
{
	t_token	*tokens = NULL;
	char	*current = input;
	char	buffer[1024];
	int		buf_index = 0;

	while (*current)
	{
		if (ft_isspace(*current))
			current++;
		else if (*current == '|')
		{
			buffer[buf_index] = '\0';
			if (buf_index > 0)
			{
				ft_add_token(&tokens, TOKEN_ARGUMENT, buffer);
				buf_index = 0;
			}
			ft_add_token(&tokens, TOKEN_PIPE, "|");
			current++;
		}
		else if (*current == '>')
		{
			buffer[buf_index] = '\0';
			if (buf_index > 0)
			{
				ft_add_token(&tokens, TOKEN_ARGUMENT, buffer);
				buf_index = 0;
			}
			if (*(current + 1) == '>')
			{
				ft_add_token(&tokens, TOKEN_REDIRECT_APPEND, ">>");
				current += 2;
			}
			else
			{
				ft_add_token(&tokens, TOKEN_REDIRECT_OUT, ">");
				current++;
			}
		}
		else if (*current == '<')
		{
			buffer[buf_index] = '\0';
			if (buf_index > 0)
			{
				ft_add_token(&tokens, TOKEN_ARGUMENT, buffer);
				buf_index = 0;
			}
			ft_add_token(&tokens, TOKEN_REDIRECT_IN, "<");
			current++;
		}
		else if (*current == '\'' || *current == '"')
		{
			char quote = *current;
			current++;
			while (*current && *current != quote)
				buffer[buf_index++] = *current++;
			if (*current == quote)
				current++;
			buffer[buf_index] = '\0';
			ft_add_token(&tokens, TOKEN_ARGUMENT, buffer);
			buf_index = 0;
		}
		else if (*current == '\\')
		{
			current++;
			if (*current)
				buffer[buf_index++] = *current++;
		}
		else
			buffer[buf_index++] = *current++;
	}
	if (buf_index > 0)
	{
		buffer[buf_index] = '\0';
		ft_add_token(&tokens, TOKEN_ARGUMENT, buffer);
	}
	return (tokens);
}
