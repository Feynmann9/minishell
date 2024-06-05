# include "../exec.h"

void    ft_echo(char *more)
{
    int i;

    i = 0;
    while (more[i])
    {
        if (more[i] == '"')
            i++;
        write(1, &more[i], 1);
        i++;
    }
    ft_printf("\n");
}