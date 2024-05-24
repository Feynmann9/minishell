/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 02:56:29 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/24 05:13:03 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

t_token	*ft_new_token(t_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_exit(2, "Error: echec malloc token.\n;");
	token->type = type;
	token->value = ft_split(value, ' ', ' ');
	token->next = NULL;
	return (token);
}

void	ft_add_token(t_token **tokens, t_type type, char *value)
{
	t_token	*new;
	t_token	*tmp;

	new = ft_new_token(type, value);
	tmp = *tokens;
	if (*tokens == NULL)
		*tokens = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_free_tokens(t_token **tokens)
{
	t_token	*tmp;
	t_token	*swap;

	tmp = *tokens;
	while (tmp)
	{
		swap = tmp->next;
		ft_free_tab2d(tmp->value);
		free(tmp);
		tmp = swap;
	}
	*tokens = NULL;
}

int	ft_process_char(t_infos *s_infos, int *buf_index, int i)
{
	if (s_infos->input[i] == '|')
		i = ft_handle_pipe(s_infos, buf_index, i);
	else if (s_infos->input[i] == '>')
		i = ft_handle_redirect_out(s_infos, buffer, buf_index, i);
	else if (s_infos->input[i] == '<')
		i = ft_handle_redirect_in(s_infos, buffer, buf_index, i);
	else if (s_infos->input[i] == '\'')
		i = ft_handle_single_quote(s_infos, buffer, buf_index, i);
	else if (s_infos->input[i] == '"')
		i = ft_handle_double_quote(s_infos, buffer, buf_index, i);
	else if (s_infos->input[i] == '$')
		i = ft_handle_env_var(s_infos, buffer, buf_index, i);
	else
		buffer[(*buf_index)++] = s_infos->input[i++];
	return (i);
}

void	ft_tokenize(t_infos *s_infos)
{
	int		buf_index;
	int		i;

	add_history(s_infos->input);
	s_infos->buffer = malloc(ft_strlen(s_infos->input));
	if (!s_infos->buffer)
		ft_quit(s_infos, "Erreur: echec malloc buffer.\n", 2);
	buf_index = 0;
	i = 0;
	while (s_infos->input[i])
	{
		if (ft_isspace(s_infos->input[i]))
			i++;
		else if (s_infos->input[i] == ' ' && buf_index == 0)
			i++;
		else
			i = ft_process_char(s_infos, &buf_index, i);
	}
	if (buf_index > 0)
	{
		s_infos->buffer[buf_index] = '\0';
		ft_add_token(&(s_infos->tokens), TOKEN_ARGUMENT, s_infos->buffer);
	}
	s_infos->buffer = ft_free_str(s_infos->buffer);
	ft_print_tokens(s_infos->tokens);
	ft_free_tokens(&(s_infos->tokens));
}
