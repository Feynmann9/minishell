/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:10:03 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/12 17:19:07 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	ft_tabsize(char *s, char c, char c2)
{
	unsigned int	i;
	unsigned int	tabcount;

	if (!s || !c || !c2)
		return (0);
	i = 0;
	tabcount = 0;
	if (s[i] == c || s[i] == c2)
		i++;
	while (s[i] != c && s[i])
	{
		if (s[i] == c2)
			break ;
		tabcount++;
		i++;
	}
	return (tabcount);
}

static int	ft_movestr(char *str, char c, char c2)
{
	int	i;

	if (!str || !c || !c2)
		return (0);
	i = 0;
	while (str[i] != c && str[i])
	{
		if (str[i] == c2)
			break ;
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c, char c2)
{
	int		i;
	int		counttab;
	char	**strs;
	char	*strtemp;

	i = 0;
	if (!s || s[0] == '\0' || !c || !c2)
		return (NULL);
	counttab = ft_countwords((char *)s, c, c2, '\0');
	strtemp = (char *)s;
	strs = (char **)malloc((counttab + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (i < counttab && strtemp[0] != '\0')
	{
		while (*strtemp == c || *strtemp == c2)
			strtemp++;
		strs[i] = ft_memlcpy(strtemp, ft_tabsize(strtemp, c, c2));
		if (!strs[i])
			return (strs = ft_free_tab2d(strs), NULL);
		strtemp += ft_movestr(strtemp, c, c2);
		i++;
	}
	return (strs[i] = NULL, strs);
}
