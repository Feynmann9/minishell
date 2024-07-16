/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:39:11 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/16 12:36:12 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "../includes/libft/includes/libft.h"
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

#define MAX_CMDS 10

//	struct pour recuperer env et comme ca on peut modifier
typedef struct s_env
{
	char			*name_folder;
	char			*value_folder;
	void			*content;
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
	//void	(*builtin)(void);
}			t_cmd;

//			init.c			//
void	init(t_base **tmp_base, t_env *ev);
void	init_env(t_env **ev, char **env);
char	*get_env_value(t_env *env, char *name);
void	builtin(t_base *base, char **env);

//			main.c			//
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

#endif
