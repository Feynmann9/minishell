/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:37:57 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/18 21:55:12 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// pour test = ./exec pwd
// pour test = ./exec env
// pour test = ./exec echo "greg le fdp"
// pour test = ./exec export nom="salope" (comment ft_env)

void	builtin(t_infos *infos)
{
	if (infos->tok->cmd[0] && infos->tok->cmd[1] == NULL)
	{
		if (ft_strcmp(infos->tok->cmd[0], "pwd") == 0)
			ft_pwd(infos);
		else if (ft_strcmp(infos->tok->cmd[0], "cd") == 0)
			ft_cd(infos, NULL);
		else if (ft_strcmp(infos->tok->cmd[0], "env") == 0)
			ft_env(infos);
		else if (ft_strcmp(infos->tok->cmd[0], "exit") == 0)
			exit(EXIT_FAILURE);
		else if (ft_strcmp(infos->tok->cmd[0], "export") == 0)
		{
			ft_order_env(infos);
			ft_print_order(infos);
		}
		else if (find_command(infos, infos->tok->cmd[0], get_env_value(infos->tmp_env, "PATH")) && infos->tok->NEXT)
		{
			//printf("test1\n");
			ft_multi(infos);
		}
		else if (find_command(infos, infos->tok->cmd[0], get_env_value(infos->tmp_env, "PATH")))
			ft_path(infos);
	}
	else if(infos->tok->cmd[0])
	{
		if (ft_strcmp(infos->tok->cmd[0], "echo") == 0)
			ft_echo(infos->tok->cmd);
		else if (ft_strcmp(infos->tok->cmd[0], "export") == 0)
			ft_export(infos, infos->tok->cmd[1]);
		else if (ft_strcmp(infos->tok->cmd[0], "unset") == 0)
			ft_unset(infos, infos->tok->cmd[1]);
		else if (ft_strcmp(infos->tok->cmd[0], "cd") == 0)
			ft_cd(infos, infos->tok->cmd[1]);
		else if (find_command(infos, infos->tok->cmd[0], get_env_value(infos->tmp_env, "PATH")) && (infos->tok->infile || infos->tok->outfile))
			handle_redirections(infos);
		else if (find_command(infos, infos->tok->cmd[0], get_env_value(infos->tmp_env, "PATH")) && infos->tok->NEXT)
		{
			//printf("test2\n");
			ft_multi(infos);
		}
		else if (find_command(infos, infos->tok->cmd[0], get_env_value(infos->tmp_env, "PATH")))
			ft_path(infos);
	}
}
