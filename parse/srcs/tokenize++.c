/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize++.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:29:58 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/24 05:05:07 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

int ft_is_valid_var_char(char c)
{
	return (isalnum(c) || c == '_');
}

int ft_handle_env_var(t_infos *s_infos, char *buffer, int *buf_index, int i)
{
    char var_name[256];
    int var_index = 0;

    i++;
    while (s_infos->input[i] && ft_is_valid_var_char(s_infos->input[i]))
        var_name[var_index++] = s_infos->input[i++];
    var_name[var_index] = '\0';
    char *var_value = getenv(var_name);
    if (var_value)
	{
        while (*var_value)
            buffer[(*buf_index)++] = *var_value++;
    }
    return i;
}

int	ft_handle_double_quote(t_infos *s_infos, char *buffer, int *buf_index, int i)
{
	char	quote;

	quote = s_infos->input[i];
	i++;
	while (s_infos->input[i] && s_infos->input[i] != quote)
		buffer[(*buf_index)++] = s_infos->input[i++];
	if (s_infos->input[i] == quote)
		i++;
	buffer[*buf_index] = '\0';
	ft_add_token(&(s_infos->tokens), TOKEN_ARGUMENT, buffer);
	*buf_index = 0;
	return (i);
}

int	ft_handle_single_quote(t_infos *s_infos, char *buffer, int *buf_index, int i)
{
	char	quote;

	quote = s_infos->input[i];
	i++;
	while (s_infos->input[i] && s_infos->input[i] != quote)
		buffer[(*buf_index)++] = s_infos->input[i++];
	if (s_infos->input[i] == quote)
		i++;
	buffer[*buf_index] = '\0';
	ft_add_token(&(s_infos->tokens), TOKEN_ARGUMENT, buffer);
	*buf_index = 0;
	return (i);
}
