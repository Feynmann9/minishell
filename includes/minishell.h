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
}               t_env;

#endif