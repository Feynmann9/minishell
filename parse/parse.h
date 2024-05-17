/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:31:51 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/17 17:46:43 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_prompt
{
	int				fd;
	char			*history_file;
	char			*input;
	char			**cmd; //[0]cat [1]-e [2]etc...
	char			**infiles;
	char			**outfiles;
	struct s_cmd	*next;
}					t_prompt;

//		input_reading.c		//

#endif
