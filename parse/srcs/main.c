/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:50:04 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/23 11:12:38 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

t_infos	ft_init_infos(void)
{
	t_infos	s_infos;

	s_infos.history_file = ".minishell_history";
	s_infos.input = NULL;
	s_infos.tokens = NULL;
	return (s_infos);
}

int	main(void)
{
	t_infos	s_infos;

	ft_sighandler();
	s_infos = ft_init_infos();
	while (1)
	{
		s_infos.input = readline("minishell> ");
		if (!s_infos.input)
			break ;
		else
			ft_tokenize(&s_infos);
	}
	rl_clear_history();
	return (0);
}
//	valgrind --suppressions=supp.supp ./parse
//	ls -l | grep 'foo' > output.txt
