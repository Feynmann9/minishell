/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:02:17 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/09 18:09:53 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	ft_strncpy_recursive(char *dest, const char *src, size_t n,
	size_t i)
{
	if (i >= n || src[i] == '\0')
	{
		if (i < n)
		{
			dest[i] = '\0';
			ft_strncpy_recursive(dest, src, n, i + 1);
		}
		return ;
	}
	dest[i] = src[i];
	ft_strncpy_recursive(dest, src, n, i + 1);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	ft_strncpy_recursive(dest, src, n, 0);
	return (dest);
}
