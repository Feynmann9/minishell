#include "../exec.h"

void    ft_cd(t_base **base)
{
    char *cd;

    cd = get_env_value((*base)->tmp_env, "HOME");
    if (cd != NULL)
    {
        (*base)->tmp_env->name_folder = "HOME";
        (*base)->tmp_env->value_folder = cd;
    }
    else
        ft_printf("erreur\n");
}