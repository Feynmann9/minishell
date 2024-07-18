/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:29:05 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/18 21:45:39 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_str(t_infos *infos, char **str, char **args)
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
		ft_quit(infos, "Error: echec malloc str.\n", 2);
	while (args[j] != NULL)
	{
		if (ft_strcmp(args[j], "|") == 0)
			break ;
		str[i] = ft_strdup(args[j]);
		if (str[i] == NULL)
			ft_quit(infos, "Error: echec malloc str[].\n", 2);
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
			ft_quit(infos, "Error: no env path\n", 2);
		full_path = find_command(infos, infos->tok->cmd[0], path_env);
		if (!full_path)
			ft_quit(infos, "Error: no full path\n", 2);
		strs = ft_str(infos, strs, infos->tok->cmd);
		execve(full_path, strs, infos->envp);
		exit(EXIT_FAILURE);
	}

/*
infos->tok->cmd --> [0] ls
infos->tok->cmd --> [1] -l

if(infos->tok->NEXT)
	infos->tok = infos->tok->NEXT

infos->tok->cmd --> [0] grep
infos->tok->cmd --> [1] minishell
*/

	pid2 = fork();
	if (pid2 < 0)
		return ;
	strs2 = NULL;
	if (pid2 == 0)
	{
		if (infos->tok->NEXT)
			infos->tok = infos->tok->NEXT;
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		path_env2 = get_env_value(infos->tmp_env, "PATH");
		if (!path_env2)
			ft_quit(infos, "Error: no env path 2\n", 2);
		full_path2 = find_command(infos, infos->tok->cmd[0], path_env2);
		if (!full_path2)
			ft_quit(infos, "Error: no full path 2\n", 2);
		strs2 = ft_str(infos, strs2, infos->tok->cmd);
		execve(full_path2, strs2, infos->envp);
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	handle_redirections(t_infos *infos)
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
	printf("0\n");
	if (pid1 == 0)
	{
		if (infos->tok->infile)
		{
			while(infos->tok->infile->NEXT)
				infos->tok->infile = infos->tok->infile->NEXT;
			fd[0] = open(infos->tok->infile->file, O_RDONLY);
			if (fd[0] < 0)
				ft_quit(infos, "Error: echec open fd[0].\n", 2);
			if (dup2(fd[0], STDIN_FILENO) < 0)
				ft_quit(infos, "Error: echec dup2 fd[0].\n", 2);
			close(fd[0]);
		}
		printf("1\n");
		if (infos->tok->outfile == NULL)
		{
			printf("2\n");
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			path_env = get_env_value(infos->tmp_env, "PATH");
			if (!path_env)
				ft_quit(infos, "Error: no env path\n", 2);
			full_path = find_command(infos, infos->tok->cmd[0], path_env);
			if (!full_path)
				ft_quit(infos, "Error: no full path\n", 2);
			printf("3\n");
			strs = ft_str(infos, strs, infos->tok->cmd);
			execve(full_path, strs, infos->envp);
			exit(EXIT_FAILURE);
		}
		printf("4\n");
	}
	printf("test before11 pid2\n");
	pid2 = fork();
	printf("test before22 pid2\n");
	if (pid2 < 0)
		return ;
	strs2 = NULL;
	if (pid2 == 0)
	{
		printf("test start outfile\n");
		if (infos->tok->NEXT)
			infos->tok = infos->tok->NEXT;
		if (infos->tok->outfile)
		{
			printf("test for outfile\n");
			while(infos->tok->outfile->NEXT)
				infos->tok->outfile = infos->tok->outfile->NEXT;
			if (infos->tok->outfile->type == TOKEN_REDIRECT_OUT)
				fd[1] = open(infos->tok->outfile->file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
			if (infos->tok->outfile->type == TOKEN_REDIRECT_APPEND)
				fd[1] = open(infos->tok->outfile->file, O_CREAT | O_WRONLY | O_APPEND, 0777);
			printf("test for create outfile\n");
			if (fd[1] < 0)
				ft_quit(infos, "Error: echec open fd[1].\n", 2);
			if (dup2(fd[1], STDOUT_FILENO) < 0)
				ft_quit(infos, "Error: echec dup2 fd[1].\n", 2);
			close(fd[1]);
		}
		if (infos->tok->infile == NULL)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			path_env2 = get_env_value(infos->tmp_env, "PATH");
			if (!path_env2)
				ft_quit(infos, "Error: echec path_env2.\n", 2);
			full_path2 = find_command(infos, infos->tok->cmd[0], path_env2);
			if (!full_path2)
				ft_quit(infos, "Error: echec full_path2_2.\n", 2);
			strs2 = ft_str(infos, strs2, infos->tok->cmd);
			execve(full_path2, strs2, infos->envp);
			exit(EXIT_FAILURE);
		}
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

/*
void	handle_redirections(t_tok *tok)
{
	//int	fd[2];
	//int pid;

	if (tok->infile)
	{
		while(tok->infile->NEXT)
			tok->infile = tok->infile->NEXT;
		fd[0] = open(tok->infile->file, O_RDONLY);
		if (fd[0] < 0)
			exit(EXIT_FAILURE);
		if (dup2(fd[0], STDIN_FILENO) < 0)
			exit(EXIT_FAILURE);
		close(fd[0]);
	}
	else if (tok->outfile)
	{
		while (tok->outfile->NEXT)
			tok->outfile = tok->outfile->NEXT;
		if (tok->outfile->type == TOKEN_REDIRECT_OUT)
			fd[1] = open(tok->outfile->file, O_WRONLY | O_CREAT, 0644);
		if (tok->outfile->type == TOKEN_REDIRECT_APPEND)
			fd[1] = open(tok->outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[1] < 0)
			exit(EXIT_FAILURE);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
		close(fd[1]);
	}
}*/

