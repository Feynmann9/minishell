/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:27:20 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/12 18:09:03 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	**ft_free_tab2d(char **input)
{
	int	i;

	if (!input)
		return (NULL);
	if (input[0])
	{
		i = 0;
		while (input[i])
		{
			input[i] = ft_free_str(input[i]);
			i++;
		}
	}
	free(input);
	return (NULL);
}
