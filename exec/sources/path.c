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

    if (pid == -1)
        return ;
    else if (pid == 0)
    {
        printf("good\n");
        //path = get_env_value((*base)->tmp_env, "PATH");
        //if (!path)
        //    return ;

    }
    else
    {
        waitpid(pid, &rien, 0);
    }
}*/
