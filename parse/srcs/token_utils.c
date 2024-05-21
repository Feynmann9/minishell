/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:21:22 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/21 19:40:49 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

t_token	*ft_new_token(token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_exit(2, "Error: echec malloc token.\n;");
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

void	ft_add_token(t_token **tokens, token_type type, char *value)
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

void	ft_free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}
