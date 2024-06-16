/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 21:00:25 by gmarquis          #+#    #+#             */
/*   Updated: 2024/06/16 21:03:14 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

/*
Retourne un nombre négatif si str1 est lexicographiquement avant str2.
Retourne 0 si les chaînes sont égales.
Retourne un nombre positif si str1 est lexicographiquement après str2.
ex:
"hello", "world" retourne un nombre négatif car 'h' est avant 'w'.
"hello", "hello" retourne 0 car les chaînes sont identiques.
"world", "hello" retourne un nombre positif car 'w' est après 'h'.
*/
