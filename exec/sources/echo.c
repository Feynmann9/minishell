# include "../exec.h"

void    ft_echo(char *more)
{
    int i;

    i = 0;
    while (more[i])
    {
        if (more[i] != '"')
        {
            write(1, &more[i], 1);
        }
        i++;
    }
    write(1, "\n", 1);
}