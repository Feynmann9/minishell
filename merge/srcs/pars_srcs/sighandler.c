/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:26:58 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/05 16:32:28 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
SIGINT = Ctrl+C
SIGQUIT = Ctrl+\
SIGTSTP = Ctrl+Z
*/
void ft_heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_redisplay();
		exit(EXIT_SUCCESS);
	}
}

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
		g_signal = 0;
	}
}

void	ft_setup_signal_handlers()
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
