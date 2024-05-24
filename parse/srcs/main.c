/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:50:04 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/24 05:06:28 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

t_infos	ft_init_infos(char **envp)
{
	t_infos	s_infos;

	s_infos.envp = envp;
	s_infos.history_file = ".minishell_history";
	s_infos.input = NULL;
	s_infos.tokens = NULL;
	return (s_infos);
}

int	main(int argc, char **argv, char **envp)
{
	t_infos	s_infos;

	if (argc != 1 || argv[1])
		ft_exit(2, "Erreur: too many arguments.\n");
	ft_sighandler();
	s_infos = ft_init_infos(envp);
	while (1)
	{
		s_infos.input = readline("minishell> ");
		if (!s_infos.input)
		{
			ft_printf("exit\n");
			break ;
		}
		else
			ft_tokenize(&s_infos);
		ft_print_tokens(s_infos.tokens);
	}
	rl_clear_history();
	return (0);
}
//	valgrind --suppressions=supp.supp ./parse
//	ls -l | grep 'foo' > output.txt
