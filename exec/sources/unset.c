#include "../exec.h"

void	ft_unset(t_base **base, char *more)
{
	while ((*base)->tmp_env)
	{
		if ((*base)->tmp_env->name_folder == more)
		{
			free((*base)->tmp_env->name_folder);
			free((*base)->tmp_env->value_folder);
			free((*base)->tmp_env->content);
			return ;
		}
		(*base)->tmp_env = (*base)->tmp_env->next;
	}
}