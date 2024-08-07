/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpp <jpp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:37:57 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/07 19:36:14 by jpp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// pour test = ./exec pwd
// pour test = ./exec env
// pour test = ./exec echo "greg le fdp"
// pour test = ./exec export nom="salope" (comment ft_env)

void	ft_solo_cmd(t_infos *infos)
{
	if (ft_strcmp(infos->tok->cmd[0], "pwd") == 0)
		ft_pwd(infos);
	else if (ft_strcmp(infos->tok->cmd[0], "cd") == 0)
		ft_cd(infos, NULL);
	else if (ft_strcmp(infos->tok->cmd[0], "env") == 0)
		ft_env(infos);
	else if (ft_strcmp(infos->tok->cmd[0], "exit") == 0)
		ft_jedois_exit(infos);
	else if (ft_strcmp(infos->tok->cmd[0], "export") == 0)
	{
		ft_order_env(infos);
		ft_print_order(infos);
	}
	else if (find_command_unleak(infos, infos->tok->cmd[0], get_env_value(infos->tmp_env, "PATH")) && (infos->tok->infile || infos->tok->outfile))
		handle_redirections(infos);
	else if (find_command_unleak(infos, infos->tok->cmd[0], get_env_value(infos->tmp_env, "PATH")) && infos->tok->NEXT)
		handle_redirections(infos);
	else if (find_command_unleak(infos, infos->tok->cmd[0], get_env_value(infos->tmp_env, "PATH")))
		ft_path(infos);
}

void	ft_multi_cmd(t_infos *infos)
{
	if (ft_strcmp(infos->tok->cmd[0], "echo") == 0)
		ft_echo(infos->tok->cmd);
	else if (ft_strcmp(infos->tok->cmd[0], "export") == 0)
		ft_export(infos, infos->tok->cmd[1]);
	else if (ft_strcmp(infos->tok->cmd[0], "unset") == 0)
		ft_unset(infos, infos->tok->cmd[1]);
	else if (ft_strcmp(infos->tok->cmd[0], "cd") == 0)
		ft_cd(infos, infos->tok->cmd[1]);
	else if (find_command_unleak(infos, infos->tok->cmd[0], get_env_value(infos->tmp_env, "PATH")) && (infos->tok->infile || infos->tok->outfile))
		handle_redirections(infos);
	else if (find_command_unleak(infos, infos->tok->cmd[0], get_env_value(infos->tmp_env, "PATH")) && infos->tok->NEXT)
		handle_redirections(infos);
	else if (find_command_unleak(infos, infos->tok->cmd[0], get_env_value(infos->tmp_env, "PATH")))
		ft_path(infos);
	else if (ft_strcmp(infos->tok->cmd[0], "exit") == 0)
		ft_jedois_exit(infos);
}

void	builtin(t_infos *infos)
{
	while (infos->tok != NULL)
	{
		if (infos->tok->cmd[0] && !find_command_unleak(infos, infos->tok->cmd[0], get_env_value(infos->tmp_env, "PATH")))
			ft_path(infos);
		if (infos->tok->cmd)
		{
			if (ft_strcmp(infos->tok->cmd[0], "./minishell") == 0)
				ft_double_minishell(infos);
			if ((infos->tok->infile || infos->tok->outfile))
				handle_redirections(infos);
			else if (infos->tok->cmd[0] && infos->tok->cmd[1] == NULL)
				ft_solo_cmd(infos);
			else if(infos->tok->cmd[0])
				ft_multi_cmd(infos);
		}
		if (infos->tok->infile || infos->tok->outfile)
		{
			if (infos->tok->infile)
				ft_printf("bash: %s: Aucun fichier ou dossier de ce type\n", infos->tok->infile->file);
			if (infos->tok->outfile)
				ft_printf("bash: %s: Aucun fichier ou dossier de ce type\n", infos->tok->outfile->file);
		}
		infos->tok = infos->tok->NEXT;
	}
}