/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:35:26 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/16 23:10:19 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*ft_new_token(t_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_exit(2, "Error: echec malloc token.\n;");
	token->type = type;
	token->value = malloc(2 * sizeof(char *));
	token->value[0] = ft_strdup(value);
	token->value[1] = NULL;
	token->NEXT = NULL;
	return (token);
}

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
	tok->buffer = malloc(tok->buffer_size);
	if (!tok->buffer)
		ft_exit(2, "Error: malloc t_t failed\n");
	ft_memset(tok->buffer, 0, BUFFER_SIZE);
	tok->tmp_buffer = NULL;
	tok->i = -1;
	tok->j = 0;
	tok->quote_char = 0;
	tok->current_type = TOKEN_COMMAND;
	tok->heredoc_buffer = NULL;
}

t_infos	ft_init_infos(char **envp)
{
	t_infos	infos;

	infos.envp = envp;
	infos.history_file = ".minishell_history";
	infos.count_pipes = 0;
	infos.input = NULL;
	infos.tokens = NULL;
	infos.tmpfile_counter = 0;
	init_env(&infos.tmp_env, envp);
	infos.tokens = NULL;
	infos.tok = NULL;
	return (infos);
}

t_tok	*ft_init_tok(void)
{
	t_tok	*new_tok;

	new_tok = malloc(sizeof(t_tok));
	if (!new_tok)
		ft_exit(2, "Error: echec malloc new_tok.\n;");
	new_tok->cmd = NULL;
	new_tok->infile = NULL;
	new_tok->outfile = NULL;
	new_tok->NEXT = NULL;
	return (new_tok);
}
