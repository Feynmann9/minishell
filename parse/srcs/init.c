/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:35:26 by gmarquis          #+#    #+#             */
/*   Updated: 2024/06/16 04:42:03 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	ft_init_tokenize_state(t_tokenize_state *state, t_infos *infos)
{
	state->input = infos->input;
	state->buffer_size = BUFFER_SIZE;
	state->buffer = malloc(state->buffer_size * sizeof(char));
	if (!state->buffer)
		ft_exit(2, "Error: malloc t_t_s failed\n");
	state->i = 0;
	state->j = 0;
	state->quote_char = 0;
	state->current_type = TOKEN_COMMAND;
}

void	ft_init_tokenizer(t_tokenizer *tok, t_infos *infos)
{
	tok->input = infos->input;
	tok->buffer_size = BUFFER_SIZE;
	tok->buffer = malloc(tok->buffer_size * sizeof(char));
	if (!tok->buffer)
		ft_exit(2, "Error: malloc t_t failed\n");
	tok->i = -1;
	tok->j = 0;
	tok->quote_char = 0;
	tok->current_type = TOKEN_COMMAND;
	tok->heredoc_buffer = NULL;
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
