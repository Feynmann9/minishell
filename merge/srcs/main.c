/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:50:04 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/22 22:14:26 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_envp(t_env *envp)
{
	t_env *tmp;

	while (envp)
	{
		tmp = envp;
		envp = envp->next;
		free(tmp->name_folder);
		free(tmp->value_folder);
		free(tmp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_infos	infos;

	if (argc != 1 || argv[1])
		ft_exit(2, "Erreur: too many arguments.\n");
	infos = ft_init_infos(envp);
	ft_sighandler();
	while (1)
	{
		infos.input = readline("minishell> ");
		add_history(infos.input);
		if (!infos.input)
		{
			rl_clear_history();
			ft_quit(&infos, "exit\n", 1);
		}
		ft_tokenize(&infos);
		ft_surcouche(&infos);
		ft_free_tokens(&infos.tokens);
		//ft_check_and_print_tok(&infos);
		if (infos.error)
		{
			ft_printf("%s\n", infos.error);
			infos.error = NULL;
		}
		else if (infos.error == NULL && infos.tok)
		{
			ft_printf("exec\n");
			builtin(&infos);
			ft_printf("post_exec\n");
		}
		ft_free_tok(&infos.tok);
		ft_free_envp(infos.tmp_env);
		infos = ft_init_infos(envp);
	}
	rl_clear_history();
	return (0);
}
