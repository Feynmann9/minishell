/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpp <jpp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:37:57 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/09 18:34:53 by jpp              ###   ########.fr       */
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
	{
		ft_echo(infos->tok->cmd);
		infos->code_error = 0;
	}
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

void	for_in_out(t_infos *infos)
{
	int fd_in;
	int fd_out;
	
	if (infos->tok->infile)
	{
		fd_in = open(infos->tok->infile->file, O_RDONLY);
		if (fd_in == -1)
			ft_printf("bash: %s: Aucun fichier ou dossier de ce type\n", infos->tok->infile->file);
		else
			close(fd_in);
	}
	if (infos->tok->outfile)
	{
		fd_out = open(infos->tok->outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
			ft_printf("bash: %s: Impossible d'ouvrir le fichier pour l'écriture\n", infos->tok->outfile->file);
		else
			close(fd_out);
	}
}

void	builtin(t_infos *infos)
{
	while (infos->tok != NULL)
	{
		if (infos->tok->cmd)
		{
			if (infos->tok->cmd[0] && !find_command_unleak(infos, infos->tok->cmd[0], get_env_value(infos->tmp_env, "PATH")))
				ft_path(infos);
			if (ft_strcmp(infos->tok->cmd[0], "./minishell") == 0)
				ft_double_minishell(infos);
			if ((infos->tok->infile || infos->tok->outfile))
				handle_redirections(infos);
			else if(infos->tok->cmd[0] && infos->tok->NEXT)
			{
				handle_redirections(infos);
				break ;
			}
			else if (infos->tok->cmd[0] && infos->tok->cmd[1] == NULL)
				ft_solo_cmd(infos);
			else if (infos->tok->cmd[0] && infos->tok->cmd[1])
				ft_multi_cmd(infos);
		}
		for_in_out(infos);
		infos->tok = infos->tok->NEXT;
	}
}
