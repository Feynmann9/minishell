#include "../exec.h"

void set_env_value(t_env *env, const char *name, const char *value)
{
    while (env)
    {
        if (strcmp(env->name_folder, name) == 0)
        {
            free(env->value_folder);
            env->value_folder = strdup(value);
            return;
        }
        env = env->next;
    }
    t_env *new_env = malloc(sizeof(t_env));
    new_env->name_folder = strdup(name);
    new_env->value_folder = strdup(value);
    new_env->next = NULL;
    t_env *current = env;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = new_env;
}

void    ft_cd(t_base **base, const char *folder)
{
    char *cd;
    char cwd[1000];

    if (folder == NULL)
    {
        cd = get_env_value((*base)->tmp_env, "HOME");
        //(*base)->tmp_env->name_folder = "HOME";
        //(*base)->tmp_env->value_folder = cd;
    }
    if (folder != NULL)
    {
        cd = ft_strdup(folder);
    }
    //else
    //    ft_printf("erreur\n");

    if (chdir(cd) != 0)
    {
        printf("erreur chdir\n");
    }
    else
    {
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            //printf("Le rep de travail courant est : %s\n", cwd);
            set_env_value((*base)->tmp_env, "PWD", cwd);
        }
        else
        {
            //printf("Le rep de travail courant est : %s\n", cwd);
            printf("erreur finish\n");
        }
    }
    //printf("chdir = %s\n", cd);
}

//utiliser chdir pour changer de folder ca permet de le faire auto
//getcwd ca permet de chercher le rep absolue et SEV permet de changer le pwd