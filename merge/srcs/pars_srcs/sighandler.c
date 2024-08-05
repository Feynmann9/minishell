/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:26:58 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/05 07:18:32 by gmarquis         ###   ########.fr       */
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
	else if (g_signal == 1)
	{
		rl_done = 1;
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		g_signal = 0;
	}
}

void	ft_setup_signal_handlers()
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
