#include "../exec.h"

int     main(int argc, char **argv)
{
    int fd[2];
    if (pipe(fd) == -1)
        return (1);

    int pid1 = fork();
    if (pid1 < 0)
        return (2);
    if (pid1 == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp(argv[1], argv[1], argv[2], NULL);
        exit(EXIT_FAILURE);
    }

    int pid2 = fork();
    if (pid2 < 0)
        return (3);
    if (pid2 == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execlp(argv[3], argv[3], argv[4], NULL);
        exit(EXIT_FAILURE);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (0);
}

void    ft_exec_pipe(t_base *base, char **env)
{
    int fd;

    while (base)
    {
        if (base->command->pipe == NULL)
        {
            // je dois tout free
            break ;

        }
        else if (base->command->pipe != NULL)
        {
            // fonction child parent fork...
            ft_with_pipe(base, env);
        }
        base = base->next;
    }
}

void    ft_with_pipe(t_base *base, char **env)
{
    int i = 0;
    
    while (i < base->command->pipe)
    {
        ft_multi(base, env);
        i++;
    }
}
