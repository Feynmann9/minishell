/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:18:34 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/16 17:18:45 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_verif_expand(t_tokenizer *tok)
{
	int	len;

	len = ft_strlen(tok->input);
	if (tok->i + ft_get_len_pre_expand(tok->buffer) < len)
	{
		if (tok->input[tok->i + ft_get_len_pre_expand(tok->buffer)] == ' ')
			return (1);
	}
	return (0);
}
