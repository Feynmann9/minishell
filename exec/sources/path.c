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

void ft_path(char *cmd)
{
    
}
