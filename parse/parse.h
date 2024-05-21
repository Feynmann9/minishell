/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:31:51 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/21 19:44:44 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_QUOTE,
	TOKEN_ESCAPE,
	TOKEN_UNKNOWN
}	token_type;

typedef struct s_token
{
	token_type		type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_infos
{
	char			*history_file;
	char			*input;
	t_token			*tokens;
}					t_infos;

//		token_utils.c	//
t_token	*ft_new_token(token_type type, char *value);
void	ft_add_token(t_token **tokens, token_type type, char *value);
void	ft_free_tokens(t_token *tokens);

//		tokenize.c		//
t_token	*ft_tokenize(char *input);

#endif
