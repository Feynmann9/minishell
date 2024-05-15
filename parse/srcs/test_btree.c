/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_btree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 01:19:02 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/15 05:37:00 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	btree_apply_prefix(t_btree *root, void (*applyf)(void *))
{
	ft_printf("%s\n", root->item);
	if (root->left != NULL)
		btree_apply_prefix(root->left, &ft_putstr_fd);
	if (root->right != NULL)
		btree_apply_prefix(root->right, );
}

t_btree *btree_create_node(void *item)
{
	t_btree *new;
	new = ft_calloc(1, sizeof(t_btree));
	new->item = item;
	return (new);
}
