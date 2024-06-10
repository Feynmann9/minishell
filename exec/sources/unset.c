#include "../exec.h"
/*
void ft_unset(t_base **base, char *more) // Attention pd utilise un char ** pour le cas ou il y a plusieurs argument (Charles a dit)
{
    t_env *current = (*base)->tmp_env;

    while (current)
	{
        if (strcmp(current->name_folder, more) == 0)
		{
            free(current->name_folder);
            free(current->value_folder);
            free(current);
            return ;
        }
        current = current->next;
    }
}*/


void ft_unset(t_base **base, char *more)
{
    t_env *current = (*base)->tmp_env;
    t_env *prev = NULL;

    while (current)
    {
        if (strcmp(current->name_folder, more) == 0)
        {
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                (*base)->tmp_env = current->next;
            }
            free(current->name_folder);
            free(current->value_folder);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}