/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:29:05 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/16 15:26:22 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_str(char **str, char **args)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (args[count] != NULL)
		count++;
	str = malloc((count + 1) * sizeof(char *));
	if (!str)
		exit(EXIT_FAILURE);
	while (args[j] != NULL)
	{
		if (strcmp(args[j], "|") == 0)
			break ;
		str[i] = strdup(args[j]);
		if (str[i] == NULL)
			exit(EXIT_FAILURE);
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	ft_multi(t_infos *infos)	//t_base *base, char **env
{
	int		fd[2];
	int		pid1;
	int		pid2;
	char	*path_env;
	char	*full_path = NULL;
	char	**strs;
	char	*path_env2;
	char	*full_path2 = NULL;
	char	**strs2;

	if (infos->envp == NULL || infos == NULL)
		return ;
	if (pipe(fd) == -1)
		return ;
	pid1 = fork();
	if (pid1 < 0)
		return ;
	strs = NULL;
	if (pid1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		path_env = get_env_value(infos->tmp_env, "PATH");
		if (!path_env)
			exit(EXIT_FAILURE);
		full_path = find_command(infos->tok->cmd[0], path_env);
		if (!full_path)
			exit(EXIT_FAILURE);
		strs = ft_str(strs, infos->tok->cmd);
		execve(full_path, strs, infos->envp);
		exit(EXIT_FAILURE);
	}

	pid2 = fork();
	if (pid2 < 0)
		return ;
	strs2 = NULL;
	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		path_env2 = get_env_value(infos->tmp_env, "PATH");
		if (!path_env2)
			exit(EXIT_FAILURE);
		full_path2 = find_command(infos->tok->cmd[3], path_env2);
		if (!full_path2)
			exit(EXIT_FAILURE);
		strs2 = ft_str(strs2, infos->tok->cmd + 3);
		execve(full_path2, strs2, infos->envp);
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
