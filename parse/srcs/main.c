/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:50:04 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/17 18:05:10 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void ft_load_history(const char *filename)
{
	read_history(filename);
}

void ft_save_history(const char *filename)
{
	write_history(filename);
}

void ft_print_history()
{
	HIST_ENTRY	**hist_list = history_list();
	int			i;

	if (hist_list)
	{
		i = 0;
		while (hist_list[i])
		{
			ft_printf("%d: %s\n", i + 1, hist_list[i]->line);
			i++;
		}
	}
}

void	ft_add_history(t_prompt *prompt)
{
	prompt->history_file = ".minishell_history";
	add_history(prompt->input);
}

char	*ft_read_input(t_prompt *prompt)
{
	ft_add_history(prompt);
	if (!ft_strncmp(prompt->input, "print history", 14))
		ft_print_history();
	if (!ft_strncmp(prompt->input, "clear history", 14))
		rl_clear_history();
	return (ft_free_str(prompt->input));
}

int main()
{
	t_prompt *prompt;

	prompt = ft_calloc(1, sizeof(prompt));

	while (1)
	{
		prompt->input = readline("minishell> ");
		if (!prompt->input)
			break;
		else
			prompt->input = ft_read_input(prompt);
	}
	ft_save_history(prompt->history_file);
	clear_history();
	return (0);
}
