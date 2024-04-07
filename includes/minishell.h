#ifndef MINISHELL
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <stdio.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_env
{
    char    *name_folder;
    char    *value_folder;
    void    *content;
    struct s_env   *next;
}               t_env;

void    new_env(t_env **ev, char *name_folder, char *value_folder);
void    init_env(t_env **ev, char **env);
void    print_env(t_env *ev);

void	ft_lstadd_front_env(t_env **lst, t_env *new);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env   *ft_lstnew_env(char *name_folder, char *value_folder);

#endif