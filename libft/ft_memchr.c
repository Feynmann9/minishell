/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matran-d <matran-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 01:20:35 by matran-d          #+#    #+#             */
/*   Updated: 2023/11/03 01:20:35 by matran-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t				i;
	unsigned char const	*s;

	i = 0;
	s = (unsigned char const *)str;
	while (i < n)
	{
		if ((s[i]) == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
