/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matran-d <matran-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:21:45 by matran-d          #+#    #+#             */
/*   Updated: 2023/11/14 19:16:11 by matran-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!src && !len)
		return (NULL);
	if (find[j] == '\0')
		return ((char *)src);
	while (src[i] != '\0' && find[j] != '\0' && i < len)
	{
		j = 0;
		if (src[i] == find[0])
		{
			while (src[i + j] == find[j] && (i + j) < len)
			{
				if (find[j + 1] == '\0')
					return ((char *)(src + i));
				j++;
			}
		}
		i++;
	}
	return (0);
}
