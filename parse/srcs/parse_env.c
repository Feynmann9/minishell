/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 01:19:02 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/16 23:30:22 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	ft_parse_prompt(t_prompt *prompt)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(1, sizeof(char));
	tmp = ft_strjoin(tmp, prompt->env[i], '\n', 0);
	i++;
	while (prompt->env[i])
	{
		tmp = ft_strjoin(tmp, prompt->env[i], '\n', 1);
		i++;
	}
	//ft_printf("[tmp] = %s\nok\n", tmp);
	prompt->cmd = ft_alt_split(tmp, '=', '\n', 0);
}

void	ft_print_cmd(char **cmd)
{
	int	i;

	i = 0;
	ft_printf("ft_print_cmd\n");
	while (cmd[i])
	{
		if (i % 2 != 0)
			ft_printf("<------------>\n");
		i++;
	}
}
