/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matran-d <matran-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:19:02 by matran-d          #+#    #+#             */
/*   Updated: 2023/11/12 13:57:20 by matran-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*range;

	i = 0;
	range = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)c)
			range = (char *)(str + i);
		i++;
	}
	if (str[i] == (unsigned char)c)
		range = (char *)(str + i);
	return (range);
}
