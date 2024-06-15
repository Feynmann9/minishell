/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:35:26 by gmarquis          #+#    #+#             */
/*   Updated: 2024/06/15 03:15:47 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	ft_init_tokenizer(t_tokenizer *tok, t_infos *infos)
{
	tok->input = infos->input;
	tok->buffer_size = BUFFER_SIZE;
	tok->buffer = malloc(tok->buffer_size * sizeof(char));
	if (!tok->buffer)
		ft_exit(1, "Error: malloc failed\n");
	tok->i = -1;
	tok->j = 0;
	tok->quote_char = 0;
	tok->current_type = TOKEN_COMMAND;
}

t_infos	ft_init_infos(char **envp)
{
	t_infos	s_infos;

	s_infos.envp = envp;
	s_infos.history_file = ".minishell_history";
	s_infos.count_pipes = 0;
	s_infos.input = NULL;
	s_infos.tokens = NULL;
	return (s_infos);
}
