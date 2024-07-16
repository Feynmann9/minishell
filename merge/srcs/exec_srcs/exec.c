/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:29:05 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/16 13:50:16 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **ft_str(char **str, char **args)
{
	int i = 0;
	int j = 0;

	int count = 0;
	while (args[count] != NULL)
		count++;

	str = (char **)malloc((count + 1) * sizeof(char *));
	if (str == NULL)
		exit(EXIT_FAILURE);

	while (args[j] != NULL)
	{
		if (strcmp(args[j], "|") == 0)
			break;
		str[i] = strdup(args[j]);
		if (str[i] == NULL)
			exit(EXIT_FAILURE);
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

void    ft_multi(t_base *base, char **env)
{
	int fd[2];

	if (env == NULL || base == NULL)
	   return ;
	if (pipe(fd) == -1)
		return ;

	int pid1 = fork();
	if (pid1 < 0)
		return ;
	char *path_env;
	char *full_path;
	char **str = NULL;
	if (pid1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		path_env = get_env_value(base->tmp_env, "PATH");
		if (!path_env)
			exit(EXIT_FAILURE);
		full_path = find_command(base->command->args[0], path_env);
		if (!full_path)
			exit(EXIT_FAILURE);
		str = ft_str(str, base->command->args);
		execve(full_path, str, env);
		exit(EXIT_FAILURE);
	}

	int pid2 = fork();
	if (pid2 < 0)
		return ;
	char *path_env2;
	char *full_path2;
	char **str2 = NULL;
	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		path_env2 = get_env_value(base->tmp_env, "PATH");
		if (!path_env2)
			exit(EXIT_FAILURE);
		full_path2 = find_command(base->command->args[3], path_env2);
		if (!full_path2)
			exit(EXIT_FAILURE);
		str2 = ft_str(str2, base->command->args + 3);
		execve(full_path2, str2, env);
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
