/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:21:22 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/27 19:22:09 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_add_token(t_infos *infos, t_token **tokens, t_type type, char *value)
{
	t_token *(new) = NULL;
	t_token *(tmp) = NULL;
	if (value == NULL || *value == '\0')
		return ;
	new = malloc(sizeof(t_token));
	if (!new)
		ft_quit(infos, "Error: malloc token failed\n", 2);
	new->type = type;
	new->value = malloc(2 * sizeof(char *));
	if (!new->value)
		ft_quit(infos, "Error: malloc token->value failed\n", 2);
	new->value[0] = ft_strdup(value);
	if (!new->value[0])
		ft_quit(infos, "Error: malloc new->value[0].\n", 2);
	new->value[1] = NULL;
	new->NEXT = NULL;
	if (*tokens == NULL)
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->NEXT)
			tmp = tmp->NEXT;
		tmp->NEXT = new;
	}
}

static void	ft_process_expanded_buffer(t_infos *infos, t_tokenizer *tok,
	char *expanded)
{
	if (ft_strchr(tok->buffer, '$'))
		tok->buffer = ft_new_ex(infos, tok->buffer, expanded);
	if (tok->tmp_buffer)
	{
		tok->buffer = ft_strjoin(tok->tmp_buffer, tok->buffer, '\0', 2);
		if (!tok->buffer)
			ft_quit(infos, "Error: echec malloc tok->buffer.\n", 2);
		tok->tmp_buffer = NULL;
	}
	else if (tok->input[tok->i] == '$')
	{
		tok->tmp_buffer = ft_strdup(tok->buffer);
		if (!tok->tmp_buffer)
			ft_quit(infos, "Error: echec malloc tok->tmp_buffer.\n", 2);
	}
	if (!tok->tmp_buffer)
		ft_add_token(infos, &infos->tokens, TOKEN_ENV, tok->buffer);
}

void	ft_add_token_from_buffer(t_infos *infos, t_tokenizer *tok, int *j)
{
	char	*expanded;

	if (*j > 0)
	{
		tok->buffer[*j] = '\0';
		if (tok->current_type == TOKEN_ENV || (tok->quote_char == '"'
				&& ft_strchr(tok->buffer, '$')) || tok->input[tok->i] == '$')
		{
			expanded = ft_expand_env_var(infos, tok->buffer, infos->envp);
			if (ft_verif_expand(tok))
				ft_add_token(infos, &infos->tokens, TOKEN_ENV, expanded);
			else
				ft_process_expanded_buffer(infos, tok, expanded);
			expanded = ft_free_str(expanded);
		}
		else
			ft_add_token(infos, &infos->tokens, tok->current_type, tok->buffer);
		*j = 0;
	}
}

void	ft_resize_buffer(t_infos *infos, t_tokenize_state *state)
{
	char	*new_buffer;

	new_buffer = malloc(state->buffer_size * 2);
	if (!new_buffer)
		ft_quit(infos, "Error: malloc failed\n", 2);
	ft_memcpy(new_buffer, state->buffer, state->buffer_size);
	state->buffer = ft_free_str(state->buffer);
	state->buffer = new_buffer;
	new_buffer = NULL;
	state->buffer_size *= 2;
}

void	ft_expand_buffer(t_infos *infos, t_tokenizer *tok)
{
	tok->new_buffer = malloc(tok->buffer_size + BUFFER_SIZE);
	if (!tok->new_buffer)
		ft_quit(infos, "Error: malloc failed\n", 2);
	ft_memcpy(tok->new_buffer, tok->buffer, tok->buffer_size);
	tok->buffer = ft_free_str(tok->buffer);
	tok->buffer = tok->new_buffer;
	tok->buffer_size += BUFFER_SIZE;
}
