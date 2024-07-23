/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:29:24 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/23 21:36:40 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	path_or_notpath(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	if (ft_strcmp(cmd, "env") == 0)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (0);
	if (ft_strcmp(cmd, "export") == 0)
		return (0);
	if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	return (1);
}

char	*find_command(t_infos *infos, char *cmd, char *path_env)
{
	if (!cmd)
		ft_quit(infos, "Error: echec malloc full_path.\n", 2);
	char *end;
	char *full_path;
	char *result;
	int	len = ft_strlen(path_env) + ft_strlen(cmd) + 1;

	full_path = malloc(len + 1);
	if (!full_path)
		ft_quit(infos, "Error: echec malloc full_path.\n", 2);
	full_path[len] = '\0';
	while (path_env && infos)
	{
		end = ft_strchr(path_env, ':');
		if (end)
			*end = '\0';
		ft_strcpy(full_path, path_env);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, cmd);
		if (access(full_path, X_OK) == 0)
		{
			result = ft_strdup(full_path);
			if (end)
				*end = ':';
			return (result);
		}
		if (end)
		{
			*end = ':';
			path_env = end + 1;
		}
		else
			path_env = NULL;
	}
	return (NULL);
}

void	ft_path(t_infos *infos)
{
	pid_t	pid = fork();
	int		rien;
	char	*path_env;
	char	*full_path = NULL;

	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		path_env = get_env_value(infos->tmp_env, "PATH");
		if (!path_env)
			exit(EXIT_FAILURE);
		full_path = find_command(infos, infos->tok->cmd[0], path_env);
		if (!full_path)
			exit(EXIT_FAILURE);
		execve(full_path, infos->tok->cmd, infos->envp);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(-1, &rien, 0);
}

void	execute_pipeline(t_infos *infos, t_cmd **commands, int num_cmds, char **env)
{
	int i = 0;
	int fd[2];
	int in_fd = 0;

	while (i < num_cmds)
	{
		pipe(fd);
		if (fork() == 0)
		{
			dup2(in_fd, 0);
			if (i < num_cmds - 1)
				dup2(fd[1], 1);
			close(fd[0]);
			char *path = find_command(infos, commands[i]->cmd, getenv("PATH"));
			if (path)
				execve(path, commands[i]->args, env);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			in_fd = fd[0];
			i++;
		}
	}
}

//char *exec_args[] = {full_path, argv[0], NULL};
//execve(full_path, exec_args, env);
