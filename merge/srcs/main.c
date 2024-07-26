/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:50:04 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/26 19:39:52 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

static t_infos	ft_re_init_infos(char **envp, t_env *tmp_env)
{
	t_infos	infos;

	infos.in_heredoc = 0;
	infos.envp = envp;
	infos.history_file = ".minishell_history";
	infos.count_pipes = 0;
	infos.input = NULL;
	infos.error = NULL;
	infos.tokens = NULL;
	infos.tmpfile_counter = 0;
	infos.tokens = NULL;
	infos.tok = NULL;
	infos.tmp_env = tmp_env;
	return (infos);
}

void	ft_free_envp(t_env *envp)
{
	t_env *tmp;

	while (envp)
	{
		tmp = envp;
		envp = envp->next;
		tmp->name_folder = ft_free_str(tmp->name_folder);
		tmp->value_folder = ft_free_str(tmp->value_folder);
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
		//ft_print_tokens(infos.tokens);
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
			//ft_printf("\n--- EXEC ---\n");
			builtin(&infos);
			//ft_printf("--- POST_EXEC ---\n");
		}
		ft_free_tok(&infos.tok);
		infos = ft_re_init_infos(envp, infos.tmp_env);
	}
	rl_clear_history();
	return (0);
}
