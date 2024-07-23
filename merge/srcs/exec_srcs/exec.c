/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:29:05 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/24 00:46:57 by gmarquis         ###   ########.fr       */
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
		// || ft_strcmp(args[j], ">") || !ft_strcmp(args[j], "<") || !ft_strcmp(args[j], ">>") || !ft_strcmp(args[j], "<<")
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
/*
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
	if (pid1 == 0)
	{
		if (infos->tok->infile)
		{
			while(infos->tok->infile->NEXT)
				infos->tok->infile = infos->tok->infile->NEXT;
			if (infos->tok->infile->type == TOKEN_REDIRECT_IN)
				fd[0] = open(infos->tok->infile->file, O_RDONLY);
			if (infos->tok->infile->type == TOKEN_HEREDOC_WORD)
				fd[0] = open(infos->tok->infile->file, O_RDONLY);
			if (fd[0] < 0)
				ft_quit(infos, "Error: echec open fd[0].\n", 2);
			if (dup2(fd[0], STDIN_FILENO) < 0)
				ft_quit(infos, "Error: echec dup2 fd[0].\n", 2);
			close(fd[0]);
		}
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
	pid2 = fork();
	if (pid2 < 0)
		return ;
	strs2 = NULL;
	if (pid2 == 0)
	{
		if (infos->tok->NEXT)
			infos->tok = infos->tok->NEXT;
		if (infos->tok->outfile)
		{
			while(infos->tok->outfile->NEXT)
				infos->tok->outfile = infos->tok->outfile->NEXT;
			if (infos->tok->outfile->type == TOKEN_REDIRECT_OUT)
				fd[1] = open(infos->tok->outfile->file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
			if (infos->tok->outfile->type == TOKEN_REDIRECT_APPEND)
				fd[1] = open(infos->tok->outfile->file, O_CREAT | O_WRONLY | O_APPEND, 0777);
			if (fd[1] < 0)
				ft_quit(infos, "Error: echec open fd[1].\n", 2);
			if (dup2(fd[1], STDOUT_FILENO) < 0)
				ft_quit(infos, "Error: echec dup2 fd[1].\n", 2);
			close(fd[1]);
		}
		close(fd[1]);
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
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
*/
/*
void handle_redirections(t_infos *infos) {
    int fd_in = -1;
    int fd_out = -1;
    pid_t pid;
    char *path_env;
    char *full_path = NULL;
    char **strs = NULL;

    if (infos->envp == NULL || infos == NULL)
        return;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        // Gérer la redirection d'entrée
        if (infos->tok->infile) {
            while (infos->tok->infile->NEXT)
                infos->tok->infile = infos->tok->infile->NEXT;

            if (infos->tok->infile->type == TOKEN_REDIRECT_IN)
                fd_in = open(infos->tok->infile->file, O_RDONLY);
            else if (infos->tok->infile->type == TOKEN_HEREDOC_WORD)
                fd_in = open(infos->tok->infile->file, O_RDONLY);

            if (fd_in < 0) {
                perror("open input file");
                exit(EXIT_FAILURE);
            }
            if (dup2(fd_in, STDIN_FILENO) < 0) {
                perror("dup2 input file");
                exit(EXIT_FAILURE);
            }
            close(fd_in);
        }

        // Gérer la redirection de sortie
        if (infos->tok->outfile) {
            while (infos->tok->outfile->NEXT)
                infos->tok->outfile = infos->tok->outfile->NEXT;

            if (infos->tok->outfile->type == TOKEN_REDIRECT_OUT)
                fd_out = open(infos->tok->outfile->file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
            else if (infos->tok->outfile->type == TOKEN_REDIRECT_APPEND)
                fd_out = open(infos->tok->outfile->file, O_CREAT | O_WRONLY | O_APPEND, 0777);

            if (fd_out < 0) {
                perror("open output file");
                exit(EXIT_FAILURE);
            }
            if (dup2(fd_out, STDOUT_FILENO) < 0) {
                perror("dup2 output file");
                exit(EXIT_FAILURE);
            }
            close(fd_out);
        }

        // Exécuter la commande
        path_env = get_env_value(infos->tmp_env, "PATH");
        if (!path_env) {
            perror("get_env_value");
            exit(EXIT_FAILURE);
        }
        full_path = find_command(infos, infos->tok->cmd[0], path_env);
        if (!full_path) {
            perror("find_command");
            exit(EXIT_FAILURE);
        }
        strs = ft_str(infos, strs, infos->tok->cmd);
        execve(full_path, strs, infos->envp);
        perror("execve");
        exit(EXIT_FAILURE);
    }

    // Attendre la fin du processus enfant
    waitpid(pid, NULL, 0);
}
*/

// Fonction pour exécuter une commande avec redirections et pipes
void handle_redirections(t_infos *infos)
{
    int **pipes;
    int i;
    int pid;
    char *path_env;
    char *full_path = NULL;
    char **args;
    t_tok *current_tok;

    if (infos->envp == NULL || infos == NULL)
        return;
    // Allocation de mémoire pour les pipes
    pipes = malloc(sizeof(int *) * infos->count_pipes);
    for (i = 0; i < infos->count_pipes; i++) {
        pipes[i] = malloc(sizeof(int) * 2);
        if (pipe(pipes[i]) == -1)
            return;
    }
    current_tok = infos->tok;
    for (i = 0; i <= infos->count_pipes; i++) {
        pid = fork();
        if (pid < 0)
            return;
        if (pid == 0) {
            // Gestion des redirections d'entrée
            if (current_tok->infile) {
                t_files *infile = current_tok->infile;
                while (infile->NEXT)
                    infile = infile->NEXT;
                int fd_in = open(infile->file, O_RDONLY);
                if (fd_in < 0)
                    exit(EXIT_FAILURE);
                if (dup2(fd_in, STDIN_FILENO) < 0)
                    exit(EXIT_FAILURE);
                close(fd_in);
            }
            // Gestion des redirections de sortie
            if (current_tok->outfile) {
                t_files *outfile = current_tok->outfile;
                while (outfile->NEXT)
                    outfile = outfile->NEXT;
                int fd_out;
                if (outfile->type == TOKEN_REDIRECT_OUT)
                    fd_out = open(outfile->file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
                else if (outfile->type == TOKEN_REDIRECT_APPEND)
                    fd_out = open(outfile->file, O_CREAT | O_WRONLY | O_APPEND, 0666);
                if (fd_out < 0)
                    exit(EXIT_FAILURE);
                if (dup2(fd_out, STDOUT_FILENO) < 0)
                    exit(EXIT_FAILURE);
                close(fd_out);
            }
            // Gestion des pipes
            if (i > 0) {
                if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0)
                    exit(EXIT_FAILURE);
            }
            if (i < infos->count_pipes) {
                if (dup2(pipes[i][1], STDOUT_FILENO) < 0)
                    exit(EXIT_FAILURE);
            }
            // Fermeture des descripteurs de fichiers inutilisés
            for (int j = 0; j < infos->count_pipes; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            // Exécution de la commande
            path_env = get_env_value(infos->tmp_env, "PATH");
            if (!path_env)
                exit(EXIT_FAILURE);
            full_path = find_command(infos, current_tok->cmd[0], path_env);
            if (!full_path)
                exit(EXIT_FAILURE);
            args = current_tok->cmd; // Assurez-vous que cmd est correctement formaté
            execve(full_path, args, infos->envp);
            exit(EXIT_FAILURE);
        }
        current_tok = current_tok->NEXT;
    }
    // Fermeture des descripteurs de fichiers dans le processus parent
    for (i = 0; i < infos->count_pipes; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    // Attente de tous les processus enfants
    for (i = 0; i <= infos->count_pipes; i++)
        wait(NULL);
    // Libération de la mémoire allouée pour les pipes
    for (i = 0; i < infos->count_pipes; i++)
        free(pipes[i]);
    free(pipes);
}


void handle_pipe(t_infos *infos) {
    int *pipes; // Tableau de descripteurs de fichiers pour les pipes
    int num_pipes = infos->count_pipes;
    int num_cmds = num_pipes + 1;
    pid_t pid;
    int i;

    if (infos->envp == NULL || infos == NULL)
        return;

    // Allouer mémoire pour les descripteurs de fichiers des pipes
    pipes = malloc(2 * num_pipes * sizeof(int));
    if (!pipes) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    // Créer les pipes
    for (i = 0; i < num_pipes; i++) {
        if (pipe(pipes + i * 2) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    // Forker pour chaque commande
    for (i = 0; i < num_cmds; i++) {
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Redirection de l'entrée
            if (i > 0) {
                dup2(pipes[(i - 1) * 2], STDIN_FILENO);
            }

            // Redirection de la sortie
            if (i < num_pipes) {
                dup2(pipes[i * 2 + 1], STDOUT_FILENO);
            }

            // Fermer tous les descripteurs de fichiers
            for (int j = 0; j < 2 * num_pipes; j++) {
                close(pipes[j]);
            }

            // Exécuter la commande
            char *path_env = get_env_value(infos->tmp_env, "PATH");
            if (!path_env) {
                perror("get_env_value");
                exit(EXIT_FAILURE);
            }
            char *full_path = find_command(infos, infos->tok->cmd[0], path_env);
            if (!full_path) {
                perror("find_command");
                exit(EXIT_FAILURE);
            }
            char **strs = ft_str(infos, NULL, infos->tok->cmd);
            execve(full_path, strs, infos->envp);
            perror("execve");
            exit(EXIT_FAILURE);
        }

        // Passer à la commande suivante
        if (i < num_pipes) {
            infos->tok = infos->tok->NEXT;
        }
    }

    // Fermer tous les descripteurs de fichiers dans le processus parent
    for (i = 0; i < 2 * num_pipes; i++) {
        close(pipes[i]);
    }

    // Attendre la fin de tous les processus enfants
    for (i = 0; i < num_cmds; i++) {
        wait(NULL);
    }

    // Libérer la mémoire
    free(pipes);
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

