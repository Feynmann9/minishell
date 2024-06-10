#include "../exec.h"

int     path_or_notpath(char *cmd)
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
/*
void ft_path(t_base **base, char *cmd, char **argv, char **env)
{
    char *path;
    pid_t pid = fork();
    int rien;

    (void)cmd;
    (void)argv;
    (void)env;
    if (pid == -1)
        return ;
    else if (pid == 0)
    {
        //printf("good\n");
        path = get_env_value((*base)->tmp_env, "PATH");
        printf("%s\n", path);
        if (!path)
            return ;
        //else
        //{
        //    access(path, 1);
        //}
        //execve(path, argv, env);

    }
    else
    {
        waitpid(pid, &rien, 0);
    }
} */

char *find_command(char *cmd, char *path_env)
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
/*
char *find_command(char *cmd, char *path_env)
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
        int i = 0;
        while (path_env[i] != '\0')
        {
            full_path[i] = path_env[i];
            i++;
        }
        full_path[i++] = '/';
        int j = 0;
        while (cmd[j] != '\0')
        {
            full_path[i++] = cmd[j++];
        }
        full_path[i] = '\0';
        //printf("%s\n", full_path);
        if (access(full_path, 1) == 0)
        {
            result = ft_strdup(full_path);
            return (result);
        }
        if (end)
            path_env = end + 1;
        else
            path_env = NULL;
    }
    return (NULL);
}
*/
void ft_path(t_base *base, char **env)
{
    pid_t pid = fork();
    int rien;
    char *path_env;
    char *full_path;

    if (pid == -1)
        exit(EXIT_FAILURE);
    else if (pid == 0)
    {
        path_env = get_env_value(base->tmp_env, "PATH");
        if (!path_env)
            exit(EXIT_FAILURE);
        full_path = find_command(base->command->cmd, path_env);
        if (!full_path)
            exit(EXIT_FAILURE);
        execve(full_path, base->command->args, env);
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(-1, &rien, 0);
    }
}

//char *exec_args[] = {full_path, argv[0], NULL};
//execve(full_path, exec_args, env);
