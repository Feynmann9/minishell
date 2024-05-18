#include "../exec.h"

void ft_unset(t_base **base, char *more) // Attention pd utilise un char ** pour le cas ou il y a plusieurs argument (Charles a dit)
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
