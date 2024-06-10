#include "../exec.h"

/*
void ft_export(t_base **base, char *more) // Attention pd utilise un char ** pour le cas ou il y a plusieurs argument (Charles a dit)
{
    char (*folder) = NULL;
    char (*value) = NULL;
    int (i) = 0;
    int (j) = 0;

    if (!(folder = malloc((ft_strlen(more)) * sizeof(char))) || base == NULL)
        return;
    if (!(value = malloc((ft_strlen(more)) * sizeof(char))))
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
    free(folder);
    free(value);
}*/

void    ft_export(t_base **base, char *more)
{
    char *folder;
    char *value;
    int i = 0;
    int j = 0;
    int size = 0;
    int val = 0;

    //printf("more start = %s\n", more);
    while (more[size] != '=' && ft_isalpha(more[size]))
        size++;
    if (!(folder = malloc(sizeof(char) * (size + 1))) || base == NULL)
        return ;
    while (more[size] != '\0')
    {
        if (more[size] != 34 && more[size] != 39)
            val++;
        size++;
    }
    if (!(value = malloc(sizeof(char) * (val + 1))))
        return (free(folder));
    while (more[i] != '=' && ft_isalpha(more[i]))
        folder[j++] = more[i++];
    folder[j] = '\0';
    //printf("foler = %s\n", folder);
    j = 0;
    while (more[i] != '\0')
    {
        if (more[i] != 34 && more[i] != 39 && more[i] != '=')
            value[j++] = more[i];
        i++;
    }
    value[j] = '\0';
    //printf("value = %s\n", value);
    add_export((*base)->tmp_env, folder, value);
    free(folder);
    free(value);
}
/*
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
}*/

void add_export(t_env *ev, char *name_folder, char *value_folder)
{
    t_env *tmp;

    if (!(tmp = malloc(sizeof(t_env))))
        return;
    tmp->name_folder = strdup(name_folder);
    tmp->value_folder = strdup(value_folder);
    tmp->next = NULL;
    if (ev != NULL)
    {
        t_env *current = ev;
        while (current->next)
            current = current->next;
        current->next = tmp;
    }
    else
    {
        ev = tmp;
    }
}
