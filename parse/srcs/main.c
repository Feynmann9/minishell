/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:50:04 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/17 03:04:38 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

int	main(int argc, char **argv, char **envp)
{
	int	i;

	if (argc != 2)
		ft_exit(2, "Error: bad argument format.\n");
	if (argv)
	{
		i = 0;
		while (envp[i])
		{
			ft_printf("%s\n", envp[i]);
			i++;
		}
	}
	return (0);
}
