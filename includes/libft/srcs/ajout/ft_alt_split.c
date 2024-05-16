/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alt_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:20:35 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/16 23:30:03 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t	ft_tabsize(char *s, char c, char c2)
{
	unsigned int	i;
	unsigned int	tabcount;

	if (!s)
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

static int	ft_verif_setings(char *s, char c, char c2, int flag)
{
	int		counttab;

	if (c == '\0' && c2 == '\0')
		c = ' ';
	if (c2 == '\0')
		c2 = c;
	if (c == '\0' && c2 != '\0')
		c = c2;
	counttab = ft_countwords(s, c, c2, '\0');
	if (flag > 5)
		flag = 0;
	return (counttab);
}

char	**ft_alt_split(char *s, char c, char c2, int flag)
{
	int		i;
	int		j;
	int		counttab;
	char	**strs;

	i = 0;
	j = 0;
	if (!s || s[0] == '\0')
		return (NULL);
	counttab = ft_verif_setings(s, c, c2, flag);
	strs = (char **)malloc((counttab + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (i < counttab && s[0] != '\0')
	{
		while (s[j] == c || s[j] == c2)
			j++;
		strs[i] = ft_memlcpy(s + j, ft_tabsize(s + j, c, c2));
		if (!strs[i])
			return (strs = ft_free_tab2d(strs), NULL);
		j += ft_movestr(s + j, c, c2);
		i++;
	}
	return (strs[i] = NULL, strs);
}
