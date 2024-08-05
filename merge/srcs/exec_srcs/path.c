/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpp <jpp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:29:24 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/05 22:36:10 by jpp              ###   ########.fr       */
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

char *construct_full_path(char *path_env, char *cmd, int len)
{
    char *full_path = malloc(len);
	if (!cmd)
		return (NULL);
    if (!full_path)
        return (NULL);
    ft_strcpy(full_path, path_env);
    ft_strcat(full_path, "/");
    ft_strcat(full_path, cmd);
    return (full_path);
}

int	check_access(t_infos *infos, char *full_path, char *end)
{
    char *result;

    if (access(full_path, X_OK) == 0)
    {
        result = ft_strdup(full_path);
        full_path = ft_free_str(full_path);
        if (!result)
            ft_quit(infos, "Error: Echec malloc result.\n", 2);
        if (end)
            *end = ':';
        result = ft_free_str(result);
        return (1);
    }
    return (0);
}

int	find_command_unleak(t_infos *infos, char *cmd, char *path_env)
{
    char	*end;
    int		len = ft_strlen(path_env) + ft_strlen(cmd) + 2;
    char	*full_path;

    while (path_env && infos)
    {
        end = ft_strchr(path_env, ':');
        if (end)
            *end = '\0';
        full_path = construct_full_path(path_env, cmd, len);
        if (!full_path)
            ft_quit(infos, "Error: echec malloc full_path.\n", 2);
        if (check_access(infos, full_path, end))
            return (1);
        if (end)
        {
            *end = ':';
            path_env = end + 1;
        }
        else
            path_env = NULL;
        full_path = ft_free_str(full_path);
    }
    return (0);
}

char *check_and_copy_path(t_infos *infos, char *full_path, char *end)
{
    char *result;

    if (access(full_path, X_OK) == 0)
    {
        result = ft_strdup(full_path);
        if (!result)
            ft_quit(infos, "Error: Echec malloc result.\n", 2);
        if (end)
            *end = ':';
        return (result);
    }
    return (NULL);
}

char *find_command(t_infos *infos, char *cmd, char *path_env)
{
    char *end;
    char *full_path;
    char *result;
    int len = ft_strlen(path_env) + ft_strlen(cmd) + 2;

    while (path_env && infos)
    {
        end = ft_strchr(path_env, ':');
        if (end)
            *end = '\0';
        full_path = construct_full_path(path_env, cmd, len);
        if (!full_path)
            ft_quit(infos, "Error: echec malloc full_path.\n", 2);
        result = check_and_copy_path(infos, full_path, end);
        free(full_path);
        if (result)
            return (result);
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

/*
int	find_command_unleak(t_infos *infos, char *cmd, char *path_env)
{
	if (!cmd)
		ft_quit(infos, "Error: echec malloc full_path.\n", 2);
	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (1);
		else
			return (0);
	}
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
			full_path = ft_free_str(full_path);
			if (!result)
				ft_quit(infos, "Error: Echec malloc result.\n", 2);
			if (end)
				*end = ':';
			result = ft_free_str(result);
			return (1);
		}
		if (end)
		{
			*end = ':';
			path_env = end + 1;
		}
		else
			path_env = NULL;
	}
	return (0);
}

char	*find_command(t_infos *infos, char *cmd, char *path_env)
{
	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			return (NULL);
	}
	char *end;
	char *full_path;
	char *result;
	int	len = ft_strlen(path_env) + ft_strlen(cmd) + 1;

	if (!cmd)
		ft_quit(infos, "Error: echec malloc full_path.\n", 2);
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
			if (!result)
				ft_quit(infos, "Error: Echec malloc result.\n", 2);
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
}*/

void ft_double_minishell(t_infos *infos)
{
	pid_t (pid) = fork();
	int		status;
	char	*path_env;

	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		ft_setup_signal_handlers();
		path_env = get_env_value(infos->tmp_env, "PATH");
		if (!path_env)
			exit(EXIT_FAILURE);
		execve(infos->tok->cmd[0], infos->tok->cmd, infos->envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		g_signal = 2;
		waitpid(pid, &status, 0);
		g_signal = 0;
	}
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
	{
		waitpid(-1, &rien, 0);
		if (WIFEXITED(rien))
			infos->code_error = WEXITSTATUS(rien);
	}
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
