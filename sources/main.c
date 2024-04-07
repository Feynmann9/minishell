#include "../includes/minishell.h"

void    new_env(t_env **ev, char *name_folder, char *value_folder)
{
    t_env *tmp;

    if (!(tmp = malloc(sizeof(t_env))))
        return (0);
    tmp->name_folder = ft_strdup(name_folder);
    tmp->value_folder = ft_strdup(value_folder);
    if (ev != NULL)
        ft_lstadd_front(ev, ft_lstnew(tmp));
    else
        ft_lstadd_back(ev, ft_lstnew(tmp));
}

void     init_env(t_env **ev, char **env)
{
    char    **tmp;
    char    **new;

    tmp = env;
    while (*tmp)
    {
        new = ft_split(*tmp, '=');
        new_add(ev, new[0], new[1]);
        tmp++;
    }
}

int     main(int argc, char **argv, char **env)
{
    t_env *ev;

    ev = NULL;
    ini_env(&ev, env);
    while (1)
    {
        printf("\033[32mCumShell $>\033[0m]");
    }
    return (0);
}