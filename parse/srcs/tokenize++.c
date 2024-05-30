/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize++.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:29:58 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/30 19:29:44 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

char	*ft_expand_env_var(char *str, char **envp)
{
	char	*var_name;
	int		i;

	var_name = str + 1;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0
			&& envp[i][ft_strlen(var_name)] == '=')
			return (ft_strdup(envp[i] + ft_strlen(var_name) + 1));
		i++;
	}
	return (ft_strdup(str));
}

void	ft_handle_quote(t_tokenizer *tok)
{
	if (tok->quote_char)
		tok->quote_char = 0;
	else
		tok->quote_char = tok->input[tok->i];
}

void	ft_handle_env_var(t_tokenizer *tok, t_infos *infos)
{
	ft_add_token_from_buffer(infos, tok, &tok->j);
	tok->current_type = TOKEN_ENV;
	tok->buffer[tok->j++] = tok->input[tok->i];
}
