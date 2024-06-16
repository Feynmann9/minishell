/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:21:22 by gmarquis          #+#    #+#             */
/*   Updated: 2024/06/16 23:59:54 by gmarquis         ###   ########.fr       */
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
	token->value = malloc(2 * sizeof(char *));
	token->value[0] = ft_strdup(value);
	token->value[1] = NULL;
	token->next = NULL;
	return (token);
}

void	ft_add_token(t_token **tokens, t_type type, char *value)
{
	t_token	*new;
	t_token	*tmp;

	if(value == NULL || *value == '\0')
		return ;
	new = malloc(sizeof(t_token));
	if (!new)
		ft_exit(2, "Error: echec malloc token.\n");
	new->type = type;
	new->value = malloc(2 * sizeof(char *));
	if (!new->value)
		ft_exit(2, "Error: echec malloc token value.\n");
	new->value[0] = ft_strdup(value);
	new->value[1] = NULL;
	new->next = NULL;
	if (*tokens == NULL)
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_add_token_from_buffer(t_infos *infos, t_tokenizer *tok, int *j)
{
	char	*expanded;

	if (*j > 0)
	{
		tok->buffer[*j] = '\0';
		if (tok->current_type == TOKEN_ENV || (tok->quote_char == '"'
				&& ft_strchr(tok->buffer, '$')))
		{
			expanded = ft_expand_env_var(tok->buffer, infos->envp);
			ft_add_token(&infos->tokens, TOKEN_ENV, expanded);
			free(expanded);
		}
		else
			ft_add_token(&infos->tokens, tok->current_type, tok->buffer);
		*j = 0;
	}
}

void	ft_resize_buffer(t_tokenize_state *state)
{
	char	*new_buffer;

	new_buffer = malloc(state->buffer_size * 2 * sizeof(char));
	if (!new_buffer)
		ft_exit(2, "Error: malloc failed\n");
	ft_memcpy(new_buffer, state->buffer, state->buffer_size);
	free(state->buffer);
	state->buffer = new_buffer;
	state->buffer_size *= 2;
}

void	ft_expand_buffer(t_tokenizer *tok)
{
	tok->new_buffer = malloc(tok->buffer_size * 2 * sizeof(char));
	if (!tok->new_buffer)
		ft_exit(1, "Error: malloc failed\n");
	ft_memcpy(tok->new_buffer, tok->buffer, tok->buffer_size);
	free(tok->buffer);
	tok->buffer = tok->new_buffer;
	tok->buffer_size *= 2;
}
