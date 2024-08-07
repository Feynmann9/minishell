/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:26:58 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/06 11:41:21 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
SIGINT = Ctrl+C
SIGQUIT = Ctrl+\
SIGTSTP = Ctrl+Z
*/
void signal_handler(int sig)
{
	if (sig == SIGINT && g_signal == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGINT && g_signal == 1)
	{
		printf("\n");
		g_signal = 0;
	}
}

void	ft_setup_signal_handlers()
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
