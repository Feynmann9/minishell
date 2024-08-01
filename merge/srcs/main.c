/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:50:04 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/01 23:23:07 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

static void	ft_re_init_infos(t_infos *infos)
{
	if(!infos)
		return ;
	infos->in_heredoc = 0;
	infos->count_pipes = 0;
	infos->input = NULL;
	infos->error = NULL;
	infos->tokens = NULL;
	infos->tmpfile_counter = 0;
	infos->tokens = NULL;
	infos->tok = NULL;
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
	ft_setup_signal_handlers();
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
		//printf("le code %d\n", infos.code_error);
		ft_free_tok(&infos.tok);
		ft_re_init_infos(&infos);
	}
	rl_clear_history();
	return (0);
}
