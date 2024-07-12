/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pour_les_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:09:23 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/12 10:46:32 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	ft_print_tokens(t_token *tokens)
{
	int		i;
	int		count_token;
	t_token	*tmp;

	tmp = tokens;
	count_token = 0;
	while (tmp)
	{
		i = 0;
		ft_printf("Type: %d, ", tmp->type);
		ft_printf("Value: %s", tmp->value[0]);
		while (tmp->value[++i])
			ft_printf(", %s", tmp->value[i]);
		ft_printf("\n");
		count_token++;
		tmp = tmp->NEXT;
	}
	ft_printf("Nombre de tokens: %d\n\n", count_token);
}
/*
bash --posix
valgrind --suppressions=supp.supp ./parse
ls -l | grep 'foo' > output.txt >> < "    foo   1" 'foo 2    ' "'fo  o 3'"
	'"foo    4"' $HOME '$HOME' "$PWD"
cat << out > outfile.txt
*/
