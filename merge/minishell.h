/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:39:11 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/05 08:36:11 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# include "../includes/libft/includes/libft.h"
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

extern int	g_signal;

//		STRUCT EXEC		//

	//	struct pour recuperer env et comme ca on peut modifier
typedef struct s_env
{
	char			*name_folder;
	char			*value_folder;
	struct s_env	*next;
}					t_env;

	//	struct pour la commande, execution de la cmd "cd, ls, pwd..."
typedef struct s_cmd
{
	char	*cmd;
	char 	*more;
	int 	pipe;
	char	**args;
}			t_cmd;

	//	struct qui compose la base de minishell
typedef struct s_base
{
	t_env			*tmp_env;
	//pid_t			pid;
	t_cmd			*command;
	struct s_base	*next;
}					t_base;

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
	t_files			*infile;	//	les infiles avec leurs type < <<
	t_files			*outfile;	//	les outfiles avec leurs type > >>
	struct s_tok	*NEXT;		//	si NEXT != NULL alors il y'a un pipe
}			t_tok;

typedef struct s_infos
{
	char			**envp;
	char			*history_file;
	char			*input;
	char			*error;
	int				in_heredoc;
	int				count_pipes;
	int				tmpfile_counter;
	int				code_error;
	t_env			*tmp_env;
	t_token			*tokens;	//	NULL
	t_tok			*tok;		//	ta partie
}					t_infos;

//			BUILTIN			//

	//			cd.c			//
void	set_env_value(t_infos *infos, t_env *env, char *name, char *value);
void	ft_cd(t_infos *infos, const char *folder);

	//			echo.c			//
void	ft_echo(char **args);

	//			export.c		//
void	ft_export(t_infos *infos, char *more);
void	add_export(t_env *ev, char *name_folder, char *value_folder);
void	ft_order_env(t_infos *infos);
void	ft_print_order(t_infos *infos);

	//			pwd.c			//
void	ft_pwd(t_infos *infos);

	//			unset			//
void	ft_unset(t_infos *infos, char *more);
int     ft_jedoistoutfaire(char *str);
void    ft_jedois_exit(t_infos *infos);
int get_last_exit_status(const char *history_file);

//			EXEC			//

	//			env.c			//
void	ft_env(t_infos *infos);

	//			exec.c			//
char	**ft_str(t_infos *infos, char **str, char **args);
void	ft_multi(t_infos *infos);
void	handle_redirections(t_infos *infos);
void	handle_pipe(t_infos *infos);

	//			start.c		//
char	*get_env_value(t_env *env, char *name);
void	builtin(t_infos *infos);

	//			path.c			//
int		path_or_notpath(char *cmd);
int		find_command_unleak(t_infos *infos, char *cmd, char *path_env);
char	*find_command(t_infos *infos, char *cmd, char *path_env);
void	ft_path(t_infos *infos);
void	execute_pipeline(t_infos *infos, t_cmd **commands, int num_cmds, char **env);
void	ft_double_minishell(t_infos *infos);

	//			init_exec.c	//
char	*get_env_value(t_env *env, char *name);
void	ft_make_env(t_infos *infos, t_env **tmp_env, char **env_var);
char	**ft_split_env(t_infos *infos, char *ligne);
t_env	*ft_init_env(t_infos *infos, char **env);

	//			utils.c			//
void	ft_lstadd_front_env(t_env **lst, t_env *new);
void	ft_lstadd_back_env(t_env **lst, t_env **new);

//		PARSE		//

	//		ex_env.c			//
int		ft_get_len_pre_expand(char *input);
char	*ft_new_ex(t_infos *infos, char *buffer, char *expanded);
char	*ft_expand_env_var(t_infos *infos, char *str, t_env *env);
void	ft_handle_env_var(t_tokenizer *tok, t_infos *infos);

	//		heredoc.c			//
void	ft_clear_heredoc_buffer(t_tokenizer *tok);
void	ft_extract_heredoc_delimiter(t_tokenizer *tok);
void	ft_collect_heredoc_lines(t_tokenizer *tok, char *delimiter, t_infos *infos);
void	ft_handle_heredoc(t_tokenizer *tok, t_infos *infos);

	//		init_parse.c				//
t_token	*ft_new_token(t_infos *infos, t_type type, char *value);
void	ft_init_tokenize_state(t_tokenize_state *state, t_infos *infos);
void	ft_init_tokenizer(t_tokenizer *tok, t_infos *infos);
t_infos	ft_init_infos(char **envp);
t_tok	*ft_init_tok(t_infos *infos);

	//		make_tmp.c			//
void	ft_generate(t_tokenizer *tok, t_infos *infos, char *delimiter);

	//		out.c				//
void	ft_free_tokens(t_token **tokens);
void	ft_quit(t_infos *s_infos, char *message, int out);
void	ft_free_tok(t_tok **tok);

	//		sighandler.c		//
void	ft_setup_signal_handlers(void);

	//		surcouche.c		//
void	ft_surcouche(t_infos *infos);

	//		token_utils.c		//
void	ft_add_token(t_infos *infos, t_token **tokens, t_type type, char *value);
void	ft_add_token_from_buffer(t_infos *infos, t_tokenizer *tok, int *j);
void	ft_resize_buffer(t_infos *infos, t_tokenize_state *state);
void	ft_expand_buffer(t_infos *infos, t_tokenizer *tok);

	//		tokenize.c			//
void	ft_handle_quote(t_tokenizer *tok);
void	ft_tokenize(t_infos *s_infos);

	//		verif.c				//
int	ft_verif_expand(t_tokenizer *tok);

	//		pour_les_tests.c	//
void	ft_print_env(t_env *ev);
void	ft_print_tokens(t_token *tokens);
void	ft_check_and_print_tok(t_infos *infos);

#endif
