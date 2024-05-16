/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 01:19:02 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/16 06:26:11 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	ft_parse_prompt(t_prompt *prompt)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(1, sizeof(char));
	tmp = ft_strjoin(tmp, prompt->env[i], '\0', 0);
	i++;
	while (prompt->env[i])
	{
		tmp = ft_strjoin(tmp, prompt->env[i], ' ', 1);
		i++;
	}
	//ft_printf("[tmp] = %s\n", tmp);
	prompt->cmd = ft_alt_split(tmp, '=', ' ');
}

void	ft_print_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		ft_printf("[%2d] %s\n", i, cmd[i]);
		i++;
	}
}
