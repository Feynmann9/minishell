/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:31:51 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/14 17:40:13 by gmarquis         ###   ########.fr       */
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
	TOKEN_HEREDOC_WORD,		//	heredoc file
	TOKEN_HEREDOC_DELIMITER,//	heredoc delimiter
	TOKEN_REDIRECT_OUT,		//	>
	TOKEN_REDIRECT_APPEND,	//	>>
	TOKEN_QUOTE,			//	''
	TOKEN_D_QUOTE,			//	""
	TOKEN_ENV,				//	$
}					t_type;

typedef struct s_token
{
	t_type			type;
	char			**value;
	struct s_token	*NEXT;
}					t_token;

//		Tu recois ca en sorti de parse		//

typedef struct s_files
{
	int				type;		//	le type du fichier. pour in = < ou <<. pour out = > ou >>
	char			*file;		//	le fichier
	struct s_files	*NEXT;		//	si NEXT != NULL alors il y'a un autre infiles
}			t_files;

typedef struct s_tok
{
	char			**cmd;		//	La liste de comande parser
	t_files			*infile;	//	les infiles avec leurs type
	t_files			*outfile;	//	les outfiles avec leurs type
	struct s_tok	*NEXT;		//	si NEXT != NULL alors il y'a un pipe
}			t_tok;

typedef struct s_infos
{
	char			**envp;
	char			*history_file;
	char			*input;
	int				count_pipes;
	int				tmpfile_counter;
	t_token			*tokens;
	t_tok			*tok;
}					t_infos;

typedef struct s_tokenize_state
{
	char			*input;
	char			*buffer;
	int				buffer_size;
	int				i;
	int				j;
	char			quote_char;
	t_type			current_type;
}					t_tokenize_state;

typedef struct s_tokenizer
{
	char	*input;
	char	*buffer;
	char	*tmp_buffer;
	char	*new_buffer;
	char	*heredoc_buffer;
	char	op[2];
	int		buffer_size;
	int		i;
	int		j;
	char	quote_char;
	t_type	current_type;
}			t_tokenizer;

//		ex_env.c			//
int		ft_get_len_pre_expand(char *input);
char	*ft_new_ex(t_infos *infos, char *buffer, char *expanded);
char	*ft_expand_env_var(t_infos *infos, char *str, char **envp);
void	ft_handle_env_var(t_tokenizer *tok, t_infos *infos);

//		heredoc.c			//
void	ft_clear_heredoc_buffer(t_tokenizer *tok);
void	ft_extract_heredoc_delimiter(t_tokenizer *tok);
void	ft_collect_heredoc_lines(t_tokenizer *tok, char *delimiter, t_infos *infos);
void	ft_handle_heredoc(t_tokenizer *tok, t_infos *infos);
void	ft_read_heredoc(t_tokenize_state *state, t_infos *infos,
	char *delimiter);

//		init.c				//
t_token	*ft_new_token(t_type type, char *value);
void	ft_init_tokenize_state(t_tokenize_state *state, t_infos *infos);
void	ft_init_tokenizer(t_tokenizer *tok, t_infos *infos);
t_infos	ft_init_infos(char **envp);

//		make_tmp.c			//
void	ft_generate(t_tokenizer *tok, t_infos *infos, char *delimiter);

//		out.c				//
void	ft_free_tokens(t_token **tokens);
void	ft_quit(t_infos *s_infos, char *message, int out);
void	ft_free_tok(t_tok *tok);

//		pour_les_tests.c	//
void	ft_print_tokens(t_token *tokens);
void	ft_check_and_print_tok(t_infos *infos);

//		sighandler.c		//
void	ft_handle_sigint(int sig);
void	ft_sighandler(void);

//		token_utils.c		//
void	ft_add_token(t_infos *infos, t_token **tokens, t_type type, char *value);
void	ft_add_token_from_buffer(t_infos *infos, t_tokenizer *tok, int *j);
void	ft_resize_buffer(t_infos *infos, t_tokenize_state *state);
void	ft_expand_buffer(t_infos *infos, t_tokenizer *tok);

//		tokenize.c			//
void	ft_handle_quote(t_tokenizer *tok);
void	ft_tokenize(t_infos *s_infos);


//		surcouche.c		//
void	ft_surcouche(t_infos *infos);

#endif
