#include "../exec.h"

void    ft_env(t_base **base)
{
    t_env *tmp;

    if (!(tmp = malloc(sizeof(t_env))))
        return ;
    tmp = (*base)->tmp_env;
    while (tmp)
    {
        ft_printf("%s=%s\n", tmp->name_folder, tmp->value_folder);
        tmp = tmp->next;
    }
}
