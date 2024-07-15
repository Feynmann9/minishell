/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:50:04 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/15 18:48:18 by gmarquis         ###   ########.fr       */
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
			ft_printf("exit\n");
			break ;
		}
		else
			ft_tokenize(&infos);
		ft_surcouche(&infos);
		//ft_exec(&infos);
	}
	rl_clear_history();
	return (0);
}
