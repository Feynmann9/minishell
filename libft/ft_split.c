/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matran-d <matran-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 02:09:03 by matran-d          #+#    #+#             */
/*   Updated: 2023/11/09 15:10:14 by matran-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char const *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == 0))
			word++;
		i++;
	}
	return (word);
}

static int	ft_mini_split(char **str, char const *s, char c, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c || s[i] == 0)
			j = i + 1;
		if (s[i] != c && ((s[i + 1] == c || s[i + 1] == 0)))
		{
			str[n] = malloc(sizeof(char) * (i - j + 2));
			if (!str[n])
			{
				while (--n >= 0)
					free(str[n]);
				free(str);
				return (0);
			}
			ft_strlcpy(str[n], (s + j), (i - j + 2));
			n++;
		}
		i++;
	}
	str[n] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**range;

	if (!s)
		return (NULL);
	range = malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!range)
		return (NULL);
	if (!ft_mini_split(range, s, c, 0))
		return (NULL);
	return (range);
}
