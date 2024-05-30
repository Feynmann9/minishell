/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pour_les_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:09:23 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/30 19:21:05 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	ft_print_tokens(t_token *tokens)
{
	int	i;

	while (tokens)
	{
		i = 0;
		ft_printf("Type: %d, ", tokens->type);
		ft_printf("Value: %s", tokens->value[0]);
		while (tokens->value[++i])
			ft_printf(", %s", tokens->value[i]);
		ft_printf("\n");
		tokens = tokens->next;
	}
}
/*
valgrind --suppressions=supp.supp ./parse
ls -l | grep 'foo' > output.txt << >> < "    foo   1" 'foo 2    ' "'fo  o 3'" '"foo    4"' $HOME '$HOME' "$PWD"
*/
