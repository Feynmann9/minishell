/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:31:51 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/15 04:17:28 by gmarquis         ###   ########.fr       */
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

//		test_btree.c		//

typedef struct s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;

void	btree_apply_prefix(t_btree *root, void (*applyf)(void *));
t_btree	*btree_create_node(void *item);

#endif
