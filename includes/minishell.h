/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:22:08 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/14 14:10:20 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <stdio.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include "libft/includes/libft.h"

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
	struct s_cmd	*cmd;
	struct s_base	*next;
}					t_base;

//	struct pour la commande, execution de la cmd "cd, ls, pwd..."
typedef struct s_cmd
{
	char	*cmd;
	void	(*builtin)(void);
}			t_cmd;

//			init.c			//
void	init(t_base **tmp_base, t_env *ev);
void	init_env(t_env **ev, char **env);
char	*get_env_value(t_env *env, char *name);
void	builtin(t_base **base, char *cmd, char *more);

//			main.c			//
void	new_env(t_env **ev, char *name_folder, char *value_folder);
void	print_env(t_env *ev);

//			utils.c			//
void	ft_lstadd_front_env(t_env **lst, t_env *new);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *name_folder, char *value_folder);

#endif
