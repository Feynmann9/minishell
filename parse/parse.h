/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:31:51 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/24 05:13:49 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../includes/minishell.h"
# include <ctype.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef enum s_type
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_QUOTE,
	TOKEN_ESCAPE,
	TOKEN_ENV,
	TOKEN_UNKNOWN
}					t_type;

typedef struct s_token
{
	t_type			type;
	char			**value;
	struct s_token	*next;
}					t_token;

typedef struct s_infos
{
	char			**envp;
	char			*history_file;
	char			*input;
	char			*buffer;
	t_token			*tokens;
}					t_infos;

//		out.c				//
void				ft_quit(t_infos *s_infos, char *message, int out);

//		pour_les_tests.c	//
void				ft_print_tokens(t_token *tokens);

//		sighandler.c		//
void				ft_handle_sigint(int sig);
void				ft_sighandler(void);

//		token_utils.c		//
int					ft_handle_redirect_in(t_infos *s_infos, char *buffer,
						int *buf_index, int i);
int					ft_handle_redirect_out(t_infos *s_infos, char *buffer,
						int *buf_index, int i);
int					ft_handle_pipe(t_infos *s_infos, int *buf_index, int i);

//		tokenize.c			//
t_token				*ft_new_token(t_type type, char *value);
void				ft_add_token(t_token **tokens, t_type type, char *value);
void				ft_free_tokens(t_token **tokens);
int					ft_process_char(t_infos *s_infos, int *buf_index, int i);
void				ft_tokenize(t_infos *s_infos);

//		tokenize++.c		//
int					ft_handle_double_quote(t_infos *s_infos, char *buffer,
						int *buf_index, int i);
int					ft_handle_single_quote(t_infos *s_infos, char *buffer,
						int *buf_index, int i);
int					ft_handle_env_var(t_infos *s_infos, char *buffer,
						int *buf_index, int i);

#endif
