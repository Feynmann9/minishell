/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matran-d <matran-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 00:57:15 by matran-d          #+#    #+#             */
/*   Updated: 2023/11/14 18:35:27 by matran-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(long n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n <= 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_maloco(long n)
{
	char	*range;
	int		i;

	i = ft_size(n);
	range = malloc(sizeof(char) * (i + 1));
	if (range == NULL)
		return (NULL);
	range[i] = '\0';
	return (range);
}

char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*range;

	i = ft_size(n);
	nb = n;
	range = ft_maloco(nb);
	if (range == NULL)
		return (NULL);
	if (nb == 0)
	{
		range[0] = '0';
		return (range);
	}
	if (nb < 0)
	{
		range[0] = '-';
		nb *= -1;
	}
	while (nb)
	{
		range[--i] = nb % 10 + 48;
		nb /= 10;
	}
	return (range);
}
