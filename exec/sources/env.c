#include "../exec.h"

void    ft_env(t_base **base)
{
    while ((*base)->tmp_env)
    {
        ft_printf("%s=%s\n", (*base)->tmp_env->name_folder, (*base)->tmp_env->value_folder);
        (*base)->tmp_env = (*base)->tmp_env->next;
    }
}