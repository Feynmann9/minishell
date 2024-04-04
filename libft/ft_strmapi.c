/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matran-d <matran-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:39:02 by matran-d          #+#    #+#             */
/*   Updated: 2023/11/07 20:17:46 by matran-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*range;
	unsigned int	i;

	i = 0;
	range = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (range == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		range[i] = f(i, s[i]);
		i++;
	}
	range[i] = '\0';
	return (range);
}
