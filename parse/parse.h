/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:31:51 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/14 17:13:22 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "../includes/minishell.h"

typedef struct s_cmd
{
	char			*cmd; //cat grep
	char			*flag; //-e
	char			**output;

	struct s_cmd	*next;
}					t_cmp;

#endif
