#include "../exec.h"

void ft_export(t_base **base, char *more) // Attention pd utilise un char ** pour le cas ou il y a plusieurs argument (Charles a dit)
{
    char (*folder) = NULL;
    char (*value) = NULL;
    int (i) = 0;
    int (j) = 0;

    if (!(folder = malloc(ft_strlen(more) * sizeof(char))) || base == NULL)
        return;
    if (!(value = malloc(ft_strlen(more) * sizeof(char))))
        return (free(folder));
    while (more[i] != '=')
        folder[j++] = more[i++];
    folder[j] = '\0';
    j = 0;
    i++;
    while (more[i] != '\0')
        value[j++] = more[i++];
    value[j] = '\0';
    add_export((*base)->tmp_env, folder, value);
}

void    add_export(t_env *ev, char *name_folder, char *value_folder)
{
    t_env *tmp;

    if (!(tmp = malloc(sizeof(t_env))))
        return ;
    tmp->name_folder = ft_strdup(name_folder);
    tmp->value_folder = ft_strdup(value_folder);
    if (ev != NULL)
        ft_lstadd_back_env(&ev, tmp);
    else
        ft_lstadd_front_env(&ev, tmp);
}
