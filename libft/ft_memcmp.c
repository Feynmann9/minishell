/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matran-d <matran-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 01:37:45 by matran-d          #+#    #+#             */
/*   Updated: 2023/11/03 01:37:45 by matran-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*ss;

	i = 0;
	s = (unsigned char *)s1;
	ss = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (s[i] == ss[i] && (i < n - 1))
		i++;
	return (s[i] - ss[i]);
}
