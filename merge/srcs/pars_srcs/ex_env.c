/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:29:58 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/05 08:47:50 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_get_len_pre_expand(char *input)
{
	int	len;

	if (input[0] != '$')
		return (0);
	input++;
	len = 0;
	while (ft_isalnum(input[len]) || input[len] == '_')
		len++;
	return (len);
}

char	*ft_new_ex(t_infos *infos, char *buffer, char *expanded)
{
	char	*new;
	int		i;
	int		j;

	i = ft_strlen(buffer);
	j = ft_strlen(expanded);
	new = malloc(j + (i - ft_get_len_pre_expand(buffer)) + 1);
	if (!new)
		ft_quit(infos, "Error: echec malloc new.\n", 2);
	i = ft_get_len_pre_expand(buffer);
	j = 0;
	while (expanded[j])
	{
		new[j] = expanded[j];
		j++;
	}
	i++;
	while (buffer[i])
	{
		new[j] = buffer[i];
		i++;
		j++;
	}
	buffer = ft_free_str(buffer);
	return (new[j] = '\0', new);
}

static char	*ft_extract_env_name(t_infos *infos, const char *input)
{
	int		len;
	char	*env_name;

	if (input[0] != '$')
		return (NULL);
	input++;
	len = 0;
	while (ft_isalnum(input[len]) || input[len] == '_')
		len++;
	env_name = malloc((len + 1));
	if (!env_name)
		ft_quit(infos, "Error: echec malloc env_name.\n", 2);
	ft_strncpy(env_name, input, len);
	env_name[len] = '\0';
	return (env_name);
}

char	*ft_expand_env_var(t_infos *infos, char *str, t_env *env)
{
	char	*var_name;
	t_env	*tmp;

	var_name = ft_extract_env_name(infos, str);
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name_folder, var_name, ft_strlen(var_name)) == 0)
		{
			if (tmp->value_folder)
				return (ft_strdup(tmp->value_folder));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_handle_env_var(t_tokenizer *tok, t_infos *infos)
{
	ft_add_token_from_buffer(infos, tok, &tok->j);
	if (tok->input[tok->i + 1] == '\'' || tok->input[tok->i + 1] == '"')
		return ;
	else if (tok->input[tok->i + 1] == '?' && tok->input[tok->i + 2] == '\0')
	{
		tok->current_type = TOKEN_COMMAND;
		tok->buffer = ft_free_str(tok->buffer);
		tok->buffer = ft_itoa(infos->code_error);
		tok->j = ft_strlen(tok->buffer);
		tok->i++;
	}
	else
	{
		tok->current_type = TOKEN_ENV;
		tok->buffer[tok->j++] = tok->input[tok->i];
	}
}
