/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:14:56 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/23 15:15:23 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	ft_quit(t_infos *s_infos, char *message, int out)
{
	ft_free_str(s_infos->buffer);
	ft_free_tokens(&(s_infos->tokens));
	ft_exit(out, message);
}
