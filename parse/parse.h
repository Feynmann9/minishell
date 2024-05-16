/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:31:51 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/16 04:53:22 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "../includes/minishell.h"

typedef struct s_prompt
{
	char			**env;
	char			**cmd; //[0]cat [1]-e [2]etc...
	char			**infiles;
	char			**outfiles;
	struct s_cmd	*next;
}					t_prompt;

//		parse_env.c		//
void	ft_parse_prompt(t_prompt *prompt);
void	ft_print_cmd(char **cmd);

#endif
