/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:39:11 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/15 21:18:11 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../includes/minishell.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <stdio.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <ctype.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

	//		STRUCT EXEC		//

//	struct pour recuperer env et comme ca on peut modifier
typedef struct s_env
{
	char			*name_folder;
	char			*value_folder;
	struct s_env	*next;
}					t_env;

//	struct qui compose la base de minishell
typedef struct s_base
{
	t_env			*tmp_env;
	pid_t			pid;
	struct s_cmd	*command;
	struct s_base	*next;
}					t_base;

//	struct pour la commande, execution de la cmd "cd, ls, pwd..."
typedef struct s_cmd
{
	char	*cmd;
	char 	*more;
	int 	pipe;
	char	**args;
}			t_cmd;

	//		STRUCT PARSE		//

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

//		pour l'exec		//

typedef struct s_files
{
	int				type;		//	le type du fichier. pour in = < ou <<. pour out = > ou >>
	char			*file;		//	le fichier
	struct s_files	*NEXT;		//	si NEXT != NULL alors il y'a un autre infiles
}			t_files;

typedef struct s_tok
{
	char			**cmd;		//	La liste de comande parser; ls -l == cmd[0] = ls; cmd[1] = -l;
	t_files			*infile;	//	les infiles avec leurs type
	t_files			*outfile;	//	les outfiles avec leurs type
	struct s_tok	*NEXT;		//	si NEXT != NULL alors il y'a un pipe
}			t_tok;

typedef struct s_infos
{
	char			*history_file;
	char			*input;
	int				count_pipes;
	int				tmpfile_counter;
	t_env			*tmp_env;
	t_token			*tokens;	//	NULL
	t_tok			*tok;		//	ta partie
}					t_infos;

//		pour le parse		//

typedef struct s_token
{
	t_type			type;
	char			**value;
	struct s_token	*NEXT;
}					t_token;

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

//			EXEC			//

//			init_exec.c			//
void	init(t_base **tmp_base, t_env *ev);
void	init_env(t_env **ev, char **env);
char	*get_env_value(t_env *env, char *name);
void	builtin(t_base *base, char **env);

//			start_exec.c			//
void	new_env(t_env **ev, char *name_folder, char *value_folder);
void	print_env(t_env *ev);

//			utils.c			//
void	ft_lstadd_front_env(t_env **lst, t_env *new);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *name_folder, char *value_folder);

//			cd.c
void	ft_cd(t_base **base, const char *folder);
void set_env_value(t_env *env, const char *name, const char *value);
//void set_env_value(t_env **env, const char *name, const char *value);
//			pwd.c
void	ft_pwd(t_base **base);

//			env.c
void    ft_env(t_base **base);

//			export.c
void    ft_export(t_base **base, char *more);
void    add_export(t_env *ev, char *name_folder, char *value_folder);

//			unset.c
void	ft_unset(t_base **base, char *more);

//			path.c
int     path_or_notpath(char *cmd);
//void ft_path(t_base **base, char *cmd, char **argv, char **env);
void ft_path(t_base *base, char **env);
char *find_command(char *cmd, char *path_env);
void    ft_echo(char **args);

//int	ft_countwords_env(char *str, char set, char set2, char end);
void	ft_split_env(char *tmp, char *new_1, char *new_2);
void    ft_order_env(t_base **base);
void    ft_print_order(t_base **base);
void split_input(char *input, t_cmd *command);

void    ft_multi(t_base *base, char **env);
char    **ft_str(char **str, char **args);

//		PARSE		//

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

//		init_parse.c				//
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
