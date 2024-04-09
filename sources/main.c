#include "../includes/minishell.h"

void    new_env(t_env **ev, char *name_folder, char *value_folder)
{
    t_env *tmp;

    if (!(tmp = malloc(sizeof(t_env))))
        return ;
    tmp->name_folder = ft_strdup(name_folder);
    tmp->value_folder = ft_strdup(value_folder);
    if (*ev != NULL)
        ft_lstadd_front_env(ev, tmp);
    else
        ft_lstadd_back_env(ev, tmp);
}

void     init_env(t_env **ev, char **env)
{
    char    **tmp;
    char    **new;

    tmp = env;
    while (*tmp)
    {
        new = ft_split(*tmp, '=');
        //printf("test1\n");
        if (new && new[0] && new[1])
        {
            new_env(ev, new[0], new[1]);
        //    printf("test2\n");
        }
        tmp++;
    }
}

void    print_env(t_env *ev)
{
    //printf("environment variable:\n");
    while (ev) 
    {
        if (strcmp(ev->name_folder, "PWD") == 0)
            printf("%s\n", ev->value_folder);
        ev = ev->next;
    }
}

int     main(int argc, char **argv, char **env)
{
    t_env *ev = NULL;
    t_base *base = NULL;
    (void)argv;
    if (argc > 3)
    {
        printf("\033[32mToo many argc, sorry\033[0m\n");
        return (0);
    }
    init_env(&ev, env);
    init(&base, ev);
    printf("\033[32mCumShell $> \033[0m");
    builtin(&base, argv[1], argv[2]);
    //print_env(ev);
    //while (1)
    //{
    //    printf("\033[32mCumShell $>\n\033[0m]");
    //}
    return (0);
}