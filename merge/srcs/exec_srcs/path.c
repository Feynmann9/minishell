/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:29:24 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/16 15:02:37 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	path_or_notpath(char *cmd)
{
	if (strcmp(cmd, "pwd") == 0)
		return (0);
	if (strcmp(cmd, "cd") == 0)
		return (0);
	if (strcmp(cmd, "env") == 0)
		return (0);
	if (strcmp(cmd, "echo") == 0)
		return (0);
	if (strcmp(cmd, "export") == 0)
		return (0);
	if (strcmp(cmd, "unset") == 0)
		return (0);
	return (1);
}

char	*find_command(char *cmd, char *path_env)
{
	char *end;
	char full_path[1000];
	char *result;

	while (path_env)
	{
		end = strchr(path_env, ':');
		if (end)
			*end = '\0';
		//printf("%s\n", end);
		//snprintf(full_path, sizeof(full_path), "%s/%s", path_env, cmd);
		strcpy(full_path, path_env);
		strcat(full_path, "/");
		strcat(full_path, cmd);
		if (access(full_path, X_OK) == 0)
		{
			result = strdup(full_path);
			//printf("Found command: %s\n", result);
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
		{
			path_env = NULL;
		}
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
		full_path = find_command(infos->tok->cmd[0], path_env);
		if (!full_path)
			exit(EXIT_FAILURE);
		execve(full_path, infos->tok->cmd, infos->envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(-1, &rien, 0);
	}
}

void	execute_pipeline(t_cmd **commands, int num_cmds, char **env)
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
			{
				dup2(fd[1], 1);
			}
			close(fd[0]);

			char *path = find_command(commands[i]->cmd, getenv("PATH"));
			if (path)
			{
				execve(path, commands[i]->args, env);
			}
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
