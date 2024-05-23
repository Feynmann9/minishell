/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 02:56:29 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/23 11:18:47 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	ft_tokenize(t_infos *s_infos)
{
	char	buffer[1024];
	char	quote;
	int		buf_index;
	int		i;

	add_history(s_infos->input);
	i = 0;
	buf_index = 0;
	while (s_infos->input[i])
	{
		if (ft_isspace(s_infos->input[i]))
			i++;
		if (s_infos->input[i] == ' ' && buf_index == 0)
			i++;
		else if (s_infos->input[i] == '|')
		{
			buffer[buf_index] = '\0';
			if (buf_index > 0)
			{
				ft_add_token(&(s_infos->tokens), TOKEN_ARGUMENT, buffer);
				buf_index = 0;
			}
			ft_add_token(&(s_infos->tokens), TOKEN_PIPE, "|");
			i++;
		}
		else if (s_infos->input[i] == '>')
		{
			buffer[buf_index] = '\0';
			if (buf_index > 0)
			{
				ft_add_token(&(s_infos->tokens), TOKEN_ARGUMENT, buffer);
				buf_index = 0;
			}
			if (s_infos->input[i + 1] == '>')
			{
				ft_add_token(&(s_infos->tokens), TOKEN_REDIRECT_APPEND, ">>");
				i += 2;
			}
			else
			{
				ft_add_token(&(s_infos->tokens), TOKEN_REDIRECT_OUT, ">");
				i++;
			}
		}
		else if (s_infos->input[i] == '<')
		{
			buffer[buf_index] = '\0';
			if (buf_index > 0)
			{
				ft_add_token(&(s_infos->tokens), TOKEN_ARGUMENT, buffer);
				buf_index = 0;
			}
			ft_add_token(&(s_infos->tokens), TOKEN_REDIRECT_IN, "<");
			i++;
		}
		else if (s_infos->input[i] == '\'' || s_infos->input[i] == '"')
		{
			quote = s_infos->input[i];
			i++;
			while (s_infos->input[i] && s_infos->input[i] != quote)
				buffer[buf_index++] = s_infos->input[i++];
			if (s_infos->input[i] == quote)
				i++;
			buffer[buf_index] = '\0';
			ft_add_token(&(s_infos->tokens), TOKEN_ARGUMENT, buffer);
			buf_index = 0;
		}
		else if (s_infos->input[i] == '\\')
		{
			i++;
			if (s_infos->input[i])
				buffer[buf_index++] = s_infos->input[i++];
		}
		else
			buffer[buf_index++] = s_infos->input[i++];
	}
	if (buf_index > 0)
	{
		buffer[buf_index] = '\0';
		ft_add_token(&(s_infos->tokens), TOKEN_ARGUMENT, buffer);
	}
	//ft_free_str(s_infos->input);
	ft_print_tokens(s_infos->tokens);	//		pour_les_tests.c
	ft_free_tokens(&(s_infos->tokens));
}
