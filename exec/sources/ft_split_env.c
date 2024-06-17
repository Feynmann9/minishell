# include "../exec.h"
/*
int	ft_countwords_env(char *str, char set, char set2, char end)
{
	int	i;
	int	check;
	int	countw;

	if (!str || !set || !set2 || str[0] == '\0')
		return (0);
	int j = 0;
	i = 0;
	check = 1;
	countw = 0;
	while (str[i] != end)
	{
		if (str[i] == set || str[i] == set2)
		{
			if (j = 0 && str[i] == set)
				j = 1;
			check = 1;
		}
		else if (check == 1)
		{
			countw++;
			check = 0;
		}
		i++;
	}
	return (countw);
}
*/
/*
char	**ft_free_tab2d(char **input)
{
	int	i;

	if (!input)
		return (NULL);
	if (input[0])
	{
		i = 0;
		while (input[i])
		{
			input[i] = ft_free_str(input[i]);
			i++;
		}
	}
	free(input);
	return (NULL);
}
char	*ft_memlcpy(char *s, size_t len)
{
	char			*str;
	unsigned int	i;

	if (!s || len == 0)
		return (0);
	i = 0;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split_env(char const *s, char c, char c2)
{
	int		i;
	int		counttab;
	char	**strs;
	char	*strtemp;

	i = 0;
	if (!s || s[0] == '\0' || !c || !c2)
		return (NULL);
	//counttab = ft_countwords_env((char *)s, c, c2, '\0');
	counttab = 2;
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
}*/
