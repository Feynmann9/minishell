/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:14:56 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/29 17:40:34 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

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

void	ft_quit(t_infos *s_infos, char *message, int out)
{
	ft_free_tokens(&(s_infos->tokens));
	ft_exit(out, message);
}
