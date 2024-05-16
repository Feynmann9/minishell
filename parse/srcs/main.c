/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:50:04 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/16 04:56:24 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

int	main(int argc, char **argv, char **env)
{
	int			i;
	t_prompt	prompt;

	if (argc != 1 && argv[1][0] == '\0')
		ft_exit(2, "Erreur: only one argument accepted.\n");
	ft_bzero(&prompt, sizeof(prompt));
	i = 0;
	prompt.env = env;
	ft_parse_prompt(&prompt);
	ft_print_cmd(prompt.cmd);
	return (0);
}
