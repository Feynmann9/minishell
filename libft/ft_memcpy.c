/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matran-d <matran-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 01:42:15 by matran-d          #+#    #+#             */
/*   Updated: 2023/11/03 01:42:15 by matran-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*de;
	unsigned char	*sr;

	i = 0;
	if ((dest == NULL) && (src == NULL))
		return (NULL);
	de = (unsigned char *)dest;
	sr = (unsigned char *)src;
	while (i < n)
	{
		de[i] = sr[i];
		i++;
	}
	return (dest);
}
