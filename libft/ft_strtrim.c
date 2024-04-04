/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matran-d <matran-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:34:01 by matran-d          #+#    #+#             */
/*   Updated: 2023/11/09 13:21:57 by matran-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char const *str, char const c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*range;
	size_t	i;
	size_t	start;
	size_t	end;

	i = 0;
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] != '\0' && ft_check(set, s1[start]))
		start++;
	while (end > start && ft_check(set, s1[end - 1]))
		end--;
	range = malloc(sizeof(char) * (end - start + 1));
	if (range == NULL)
		return (NULL);
	while (start < end)
	{
		range[i] = s1[start];
		start++;
		i++;
	}
	range[i] = '\0';
	return (range);
}
