#include "minishell.h"
#include <stdio.h>  // Pour les déclarations de débogage
#include <stdlib.h> // Pour exit()

char **ft_str(t_infos *infos, char **str, char **args) {
    int i = 0, j = 0, count = 0;

    while (args[count] != NULL)
        count++;

    str = malloc((count + 1) * sizeof(char *));
    if (!str)
        ft_quit(infos, "Error: echec malloc str.\n", 2);

    while (args[j] != NULL) {
        if (ft_strcmp(args[j], "|") == 0)
            break;

        str[i] = ft_strdup(args[j]);
        if (str[i] == NULL)
            ft_quit(infos, "Error: echec malloc str[].\n", 2);

        j++;
        i++;
    }
    str[i] = NULL;
    return str;
}

void ft_multi(t_infos *infos) {
    int fd[2];
    pid_t pid1, pid2;
    char *path_env, *full_path = NULL;
    char **strs = NULL;
    char *path_env2, *full_path2 = NULL;
    char **strs2 = NULL;

    if (infos == NULL || infos->envp == NULL) {
        fprintf(stderr, "Error: infos or infos->envp is NULL\n");
        return;
    }

    if (pipe(fd) == -1) {
        perror("Error creating pipe");
        return;
    }

    pid1 = fork();
    if (pid1 < 0) {
        perror("Error creating first child process");
        return;
    }

    if (pid1 == 0) {
        close(fd[0]);
        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            perror("Error duplicating file descriptor for stdout");
            exit(EXIT_FAILURE);
        }
        close(fd[1]);

        path_env = get_env_value(infos->tmp_env, "PATH");
        if (!path_env) {
            fprintf(stderr, "Error: failed to get PATH\n");
            exit(EXIT_FAILURE);
        }

        full_path = find_command(infos, infos->tok->cmd[0], path_env);
        if (!full_path) {
            fprintf(stderr, "Error: failed to find command\n");
            exit(EXIT_FAILURE);
        }

        strs = ft_str(infos, strs, infos->tok->cmd);
        execve(full_path, strs, infos->envp);
        perror("Error executing first command");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("Error creating second child process");
        return;
    }

    if (pid2 == 0) {
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1) {
            perror("Error duplicating file descriptor for stdin");
            exit(EXIT_FAILURE);
        }
        close(fd[0]);

        path_env2 = get_env_value(infos->tmp_env, "PATH");
        if (!path_env2) {
            fprintf(stderr, "Error: failed to get PATH\n");
            exit(EXIT_FAILURE);
        }

        full_path2 = find_command(infos, infos->tok->cmd[0], path_env2);
        if (!full_path2) {
            fprintf(stderr, "Error: failed to find command\n");
            exit(EXIT_FAILURE);
        }

        strs2 = ft_str(infos, strs2, infos->tok->cmd);
        execve(full_path2, strs2, infos->envp);
        perror("Error executing second command");
        exit(EXIT_FAILURE);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
