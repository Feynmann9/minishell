/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:26:58 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/23 18:51:11 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_handle_sigint(int sig)
{
	if (g_signal == 1)
	{
		g_signal = 0;
		exit(1);
	}
	else if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_sighandler(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(EXIT_SUCCESS);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGTSTP, &sa, NULL) == -1)
		exit(EXIT_SUCCESS);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		exit(EXIT_SUCCESS);
}
