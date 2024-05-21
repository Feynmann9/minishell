/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:50:04 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/21 19:42:57 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	ft_print_tokens(t_token *tokens)
{
	while (tokens)
	{
		ft_printf("Type: %d, Value: %s\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

t_infos	ft_init_infos()
{
	t_infos	s_infos;

	s_infos.history_file = ".minishell_history";
	s_infos.input = NULL;
	s_infos.tokens = NULL;
	return (s_infos);
}

int main()
{
	t_infos	s_infos;

	s_infos = ft_init_infos();
	while (1)
	{
		s_infos.input = readline("minishell> ");
		if (!s_infos.input)
			break;
		else
		{
			add_history(s_infos.input);
			s_infos.tokens = ft_tokenize(s_infos.input);
			s_infos.input = ft_free_str(s_infos.input);
		}
	}
	ft_print_tokens(s_infos.tokens);
	ft_free_tokens(s_infos.tokens);
	rl_clear_history();
	return (0);
}
//	valgrind --suppressions=supp.supp ./parse
//	ls -l | grep 'foo' > output.txt
