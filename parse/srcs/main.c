/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:50:04 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/14 17:14:01 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

int	main(int argc, char **argv, char **env)
{
	int	i;

	if (argc != 2)
		ft_exit(2, "Error: bad argument format.\n");
	i = 0;
	ft_printf("argv 1 = %s\nargv 2 = %s\n\n", argv[0], argv[1]);
	while (env[i])
	{
		ft_printf("env:\n%s", env[i]);
		i++;
	}
	return (0);
}
