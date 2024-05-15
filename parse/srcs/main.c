/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:50:04 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/15 04:11:38 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

int	main(int argc, char **argv, char **env)
{
	t_btree btree;

	argc = 0;
	argv = NULL;
	ft_bzero(&btree, sizeof(t_btree));
	btree.item = env[0];
	btree.left = btree_create_node(env[1]);
	btree.right = btree_create_node(env[2]);
	ft_printf("0 = %s\n", btree.item);
	ft_printf("1 = %s\n", btree.left->item);
	ft_printf("2 = %s\n", btree.right->item);
	free(btree.left);
	free(btree.right);
	return (0);
}
