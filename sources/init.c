#include "../includes/minishell.h"

void init(t_base **tmp_base, t_env *ev)
{
    (*tmp_base) = malloc(sizeof(t_base));
    if ((*tmp_base) != NULL)
    {
        (*tmp_base)->tmp_env = ev;
        (*tmp_base)->pid = 0;
        (*tmp_base)->next = NULL;
    }
    else 
        exit(EXIT_FAILURE);
}

char *get_env_value(t_env *env, char *name)
{
    while (env != NULL)
    {
        if (strcmp(env->name_folder, name) == 0)
            return (env->value_folder);
        env = env->next;
    }
    return (NULL);
}

void builtin(t_base **base, char *cmd, char *more)
{
    if (more == NULL)
    {
        if (strcmp(cmd, "PWD") == 0)
        {
            char *pwd = get_env_value((*base)->tmp_env, "PWD");
            if (pwd != NULL)
                printf("%s\n", pwd);
            else
                printf("erreur\n");
        }
    }
    if (more != NULL)
    {
        if (strcmp(cmd, "echo") == 0)
            printf("%s\n", more);
        else
            printf("erreur\n");
    }
}
