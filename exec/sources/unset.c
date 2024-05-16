#include "../exec.h"

void ft_unset(t_base **base, char *more)
{
    t_env *current = (*base)->tmp_env;

    while (current)
	{
        if (strcmp(current->name_folder, more) == 0)
		{
            free(current->name_folder);
            free(current->value_folder);
            free(current->content);
            return;
        }
        current = current->next;
    }
}