/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:50:04 by gmarquis          #+#    #+#             */
/*   Updated: 2024/06/16 01:03:44 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

int	main(int argc, char **argv, char **envp)
{
	t_infos	infos;

	if (argc != 1 || argv[1])
		ft_exit(2, "Erreur: too many arguments.\n");
	ft_sighandler();
	infos = ft_init_infos(envp);
	while (1)
	{
		infos.input = readline("minishell> ");
		add_history(infos.input);
		if (!infos.input)
		{
			printf("exit\n");
			break ;
		}
		else
			ft_tokenize(&infos);
		ft_print_tokens(infos.tokens);
		ft_free_tokens(&infos.tokens);
	}
	rl_clear_history();
	return (0);
}
