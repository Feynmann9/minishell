/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:21:22 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/24 05:14:58 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

int	ft_handle_redirect_in(t_infos *s_infos, char *buffer, int *buf_index, int i)
{
	buffer[*buf_index] = '\0';
	if (*buf_index > 0)
	{
		ft_add_token(&(s_infos->tokens), TOKEN_ARGUMENT, buffer);
		*buf_index = 0;
	}
	ft_add_token(&(s_infos->tokens), TOKEN_REDIRECT_IN, "<");
	return (i + 1);
}

int	ft_handle_redirect_out(t_infos *s_infos, char *buffer, int *buf_index,
		int i)
{
	buffer[*buf_index] = '\0';
	if (*buf_index > 0)
	{
		ft_add_token(&(s_infos->tokens), TOKEN_ARGUMENT, buffer);
		*buf_index = 0;
	}
	if (s_infos->input[i + 1] == '>')
	{
		ft_add_token(&(s_infos->tokens), TOKEN_REDIRECT_APPEND, ">>");
		return (i + 2);
	}
	else
	{
		ft_add_token(&(s_infos->tokens), TOKEN_REDIRECT_OUT, ">");
		return (i + 1);
	}
}

int	ft_handle_pipe(t_infos *s_infos, int *buf_index, int i)
{
	s_infos->buffer[*buf_index] = '\0';
	if (*buf_index > 0)
	{
		ft_add_token(&(s_infos->tokens), TOKEN_ARGUMENT, s_infos->buffer);
		*buf_index = 0;
	}
	ft_add_token(&(s_infos->tokens), TOKEN_PIPE, "|");
	return (i + 1);
}
