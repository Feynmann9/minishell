/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matran-d <matran-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 01:58:20 by matran-d          #+#    #+#             */
/*   Updated: 2023/11/14 18:26:04 by matran-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	t;

	i = 0;
	p = ptr;
	t = (unsigned char)value;
	while (i < num)
	{
		p[i] = t;
		i++;
	}
	return (ptr);
}
