/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matran-d <matran-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 00:44:42 by matran-d          #+#    #+#             */
/*   Updated: 2023/11/14 17:01:33 by matran-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*alloc;
	size_t	i;

	if (size == 0)
		return (malloc(0));
	if (count > (2147483647 / size))
		return (NULL);
	alloc = (void *)malloc(count * size);
	if (!alloc)
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		((char *)alloc)[i] = 0;
		i++;
	}
	return (alloc);
}
