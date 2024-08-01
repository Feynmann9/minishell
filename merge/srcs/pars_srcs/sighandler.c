/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:26:58 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/01 23:26:14 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void signal_handler(int sig)
{
	if (g_signal == 0)
	{
		if (sig == SIGINT)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (g_signal == 1)
	{
		if (sig == SIGINT)
		{
			printf("\n");
			rl_replace_line("", 0);
			rl_redisplay();
			g_signal = 0;
		}
	}
}

void	ft_setup_signal_handlers()
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTERM, signal_handler);
}
