# include "../exec.h"

void    ft_echo(char **args)
{
    int back = 0;
    int i;
    int j = 1;

    if (args[j] && strcmp(args[j], "-n") == 0)
    {
        back = 1;
        j++;
    }
    while (args[j])
    {
        i = 0;
        while (args[j][i] != '\0')
        {
            if (args[j][i] != '"')
                write(1, &args[j][i], 1);
            i++;
        }
        if (args[j + 1])
            write(1, " ", 1);
        j++;
    }
    if (back == 0)
        write(1, "\n", 1);
}