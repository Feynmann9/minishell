/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:09:36 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/12 17:17:03 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;
	int		trigger;

	if (argc != 2)
		ft_exit(2, "Erreur!\n");
	fd = open(argv[1], O_RDONLY);
	i = 0;
	trigger = 1;
	printf("| v v | start a la ligne d'en dessou en blanc | v v |\n");
	while (trigger == 1)
	{
		line = get_next_line(fd, 0);
		if (line != NULL)
			printf("| %3d |%s", i, line);
		else
			trigger = 0;
		free(line);
		i++;
	}
	printf("| ^ ^ |   fin a la ligne du dessus en blanc   | ^ ^ |\n");
	return (0);
}
