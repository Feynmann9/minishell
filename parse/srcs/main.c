/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:50:04 by gmarquis          #+#    #+#             */
/*   Updated: 2024/05/18 07:48:39 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

t_infos	ft_init_infos()
{
	t_infos	s_infos;

	s_infos.history_file = ".minishell_history";
	s_infos.input = NULL;
	return (s_infos);
}

t_token	*ft_new_token(token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_exit(2, "Error: echec malloc token.\n;");
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

void	ft_add_token(t_token **tokens, token_type type, char *value)
{
	t_token	*new = ft_new_token(type, value);
	t_token	*temp = *tokens;

	if (*tokens == NULL)
		*tokens = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	ft_free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
	}
}

void	ft_print_tokens(t_token *tokens)
{
	while (tokens)
	{
		ft_printf("Type: %d, Value: %s\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

t_token	*ft_tokenize(char *input)
{
	t_token	*tokens = NULL;
	char	*current = input;
	char	buffer[1024];
	int		buf_index = 0;

	while (*current)
	{
		if (isspace(*current))
			current++;
		else if (*current == '|')
		{
			buffer[buf_index] = '\0';
			if (buf_index > 0)
			{
				ft_add_token(&tokens, TOKEN_ARGUMENT, buffer);
				buf_index = 0;
			}
			ft_add_token(&tokens, TOKEN_PIPE, "|");
			current++;
		}
		else if (*current == '>')
		{
			buffer[buf_index] = '\0';
			if (buf_index > 0)
			{
				ft_add_token(&tokens, TOKEN_ARGUMENT, buffer);
				buf_index = 0;
			}
			if (*(current + 1) == '>')
			{
				ft_add_token(&tokens, TOKEN_REDIRECT_APPEND, ">>");
				current += 2;
			}
			else
			{
				ft_add_token(&tokens, TOKEN_REDIRECT_OUT, ">");
				current++;
			}
		}
		else if (*current == '<')
		{
			buffer[buf_index] = '\0';
			if (buf_index > 0)
			{
				ft_add_token(&tokens, TOKEN_ARGUMENT, buffer);
				buf_index = 0;
			}
			ft_add_token(&tokens, TOKEN_REDIRECT_IN, "<");
			current++;
		}
		else if (*current == '\'' || *current == '"')
		{
			char quote = *current;
			current++;
			while (*current && *current != quote)
				buffer[buf_index++] = *current++;
			if (*current == quote)
				current++;
			buffer[buf_index] = '\0';
			ft_add_token(&tokens, TOKEN_ARGUMENT, buffer);
			buf_index = 0;
		}
		else if (*current == '\\')
		{
			current++;
			if (*current)
				buffer[buf_index++] = *current++;
		}
		else
			buffer[buf_index++] = *current++;
	}
	if (buf_index > 0)
	{
		buffer[buf_index] = '\0';
		ft_add_token(&tokens, TOKEN_ARGUMENT, buffer);
	}
	return (tokens);
}

int main()
{
	t_infos	s_infos;
	t_token	*tokens;

	s_infos = ft_init_infos();
//	tokens = ft_init_token();
	while (1)
	{
		s_infos.input = readline("minishell> "); // leak ? utiliser supp.supp
		if (!s_infos.input)
			break;
		else
		{
			add_history(s_infos.input); // leak ?
			tokens = ft_tokenize(s_infos.input);
			s_infos.input = ft_free_str(s_infos.input);
		}
	}
	ft_print_tokens(tokens);
	ft_free_tokens(tokens);
	rl_clear_history(); // leak ?
	return (0);
}

//	ls -l | grep 'foo' > output.txt
