#include "../exec.h"

void	ft_pwd(t_base **base)
{
	char	*pwd;

	pwd = get_env_value((*base)->tmp_env, "PWD");
	if (pwd != NULL)
		printf("%s\n", pwd);
	else
		printf("erreur\n");
}
