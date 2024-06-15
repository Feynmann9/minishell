/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:31:51 by gmarquis          #+#    #+#             */
/*   Updated: 2024/06/15 05:25:06 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

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
	TOKEN_PIPE,				//	|
	TOKEN_REDIRECT_IN,		//	<
	TOKEN_HEREDOC,			//	<<
	TOKEN_REDIRECT_OUT,		//	>
	TOKEN_REDIRECT_APPEND,	//	>>
	TOKEN_QUOTE,			//	''
	TOKEN_D_QUOTE,			//	""
	TOKEN_ENV,				//	$
}					t_type;

typedef struct s_lists
{
	void			*content;
	struct s_lists	*next;
}					t_lists;

typedef struct s_command
{
	char			**args;			// Arguments de la commande
	int				args_count;		// Nombre d'arguments
	char			*input_file;	// Fichier d'entrée (pour '<')
	char			*output_file;	// Fichier de sortie (pour '>')
	char			*append_file;	// Fichier pour append (pour '>>')
	char			*heredoc_delim;	// Délimiteur pour heredoc (pour '<<')
}					t_command;

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
	int				count_pipes;
	t_token			*tokens;
}					t_infos;

typedef struct s_tokenizer
{
	char	*input;
	char	*buffer;
	char	*new_buffer;
	char	op[2];
	int		buffer_size;
	int		i;
	int		j;
	char	quote_char;
	t_type	current_type;
}			t_tokenizer;

//		init.c				//
void	ft_init_tokenizer(t_tokenizer *tok, t_infos *infos);
t_infos	ft_init_infos(char **envp);

//		out.c				//
void	ft_free_tokens(t_token **tokens);
void	ft_quit(t_infos *s_infos, char *message, int out);

//		pour_les_tests.c	//
void	ft_print_tokens(t_token *tokens);

//		sighandler.c		//
void	ft_handle_sigint(int sig);
void	ft_sighandler(void);

//		token_utils.c		//
t_token	*ft_new_token(t_type type, char *value);
void	ft_add_token(t_token **tokens, t_type type, char *value);
void	ft_add_token_from_buffer(t_infos *infos, t_tokenizer *tok, int *j);
void	ft_expand_buffer(t_tokenizer *tok);

//		tokenize.c			//
t_type	ft_get_token_type(char *str);
void	ft_tokenize(t_infos *s_infos);

//		tokenize++.c		//
char	*ft_expand_env_var(char *str, char **envp);
void	ft_handle_quote(t_tokenizer *tok);
void	ft_handle_env_var(t_tokenizer *tok, t_infos *infos);

//		surcouche.c		//
void	ft_surcouche(t_infos *infos);

#endif
