/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:10:30 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/09 06:49:41 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char *s1, char *s2, char set, int flag)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	if (set != '\0')
		str = malloc(((ft_strlen(s1) + ft_strlen(s2)) + 2) * sizeof(char));
	else
		str = malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (!str)
		return (0);
	i = -1;
	j = 0;
	while (s1[++i])
		str[i] = s1[i];
	if (set != '\0')
		str[i++] = set;
	while (s2[j])
		str[i++] = s2[j++];
	if (flag >= 1)
		free(s1);
	if (flag == 2)
		free(s2);
	return (str[i] = '\0', str);
}
