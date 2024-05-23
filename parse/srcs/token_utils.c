/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:21:22 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/23 11:11:16 by gmarquis         ###   ########.fr       */
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
