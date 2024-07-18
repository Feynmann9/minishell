/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:37:45 by gmarquis          #+#    #+#             */
/*   Updated: 2024/07/18 19:43:21 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*void ft_export(t_base **base, char *more) // Attention pd utilise un char ** pour le cas ou il y a plusieurs argument (Charles a dit)
{
	char (*folder) = NULL;
	char (*value) = NULL;
	int (i) = 0;
	int (j) = 0;

	if (!(folder = malloc((ft_strlen(more)) * sizeof(char))) || base == NULL)
		return;
	if (!(value = malloc((ft_strlen(more)) * sizeof(char))))
		return (free(folder));
	while (more[i] != '=')
		folder[j++] = more[i++];
	folder[j] = '\0';
	j = 0;
	i++;
	while (more[i] != '\0')
		value[j++] = more[i++];
	value[j] = '\0';
	add_export((*base)->tmp_env, folder, value);
	free(folder);
	free(value);
}*/

void	ft_export(t_infos *infos, char *more)
{
	char	*folder;
	char	*value;
	int		i = 0;
	int		j = 0;
	int		size = 0;
	int		val = 0;

	while (more[size] != '=' && ft_isalpha(more[size]))
		size++;
	if (!(folder = malloc(sizeof(char) * (size + 1))) || infos)
		return ;
	while (more[size] != '\0')
	{
		if (more[size] != 34 && more[size] != 39)
			val++;
		size++;
	}
	if (!(value = malloc(sizeof(char) * (val + 1))))
		return (free(folder));
	while (more[i] != '=' && ft_isalpha(more[i]))
		folder[j++] = more[i++];
	folder[j] = '\0';
	//printf("foler = %s\n", folder);
	j = 0;
	while (more[i] != '\0')
	{
		if (more[i] != 34 && more[i] != 39 && more[i] != '=')
			value[j++] = more[i];
		i++;
	}
	value[j] = '\0';
	//printf("value = %s\n", value);
	add_export(infos->tmp_env, folder, value);
	free(folder);
	free(value);
}

/*void    add_export(t_env *ev, char *name_folder, char *value_folder)
{
	t_env *tmp;

	if (!(tmp = malloc(sizeof(t_env))))
		return ;
	tmp->name_folder = ft_strdup(name_folder);
	tmp->value_folder = ft_strdup(value_folder);
	if (ev != NULL)
		ft_lstadd_back_env(&ev, tmp);
	else
		ft_lstadd_front_env(&ev, tmp);
}*/

void	add_export(t_env *ev, char *name_folder, char *value_folder)
{
	t_env *tmp;
	int i = 0;

	if (!(tmp = malloc(sizeof(t_env))))
		return;
	tmp->name_folder = ft_strdup(name_folder);
	tmp->value_folder = ft_strdup(value_folder);
	tmp->next = NULL;
	if (ev != NULL)
	{
		t_env *current = ev;
		while (current->next)
		{
			if (ft_strcmp(current->next->name_folder, tmp->name_folder) == 0)
			{
				i = 1;
				current->next->value_folder = tmp->value_folder;
			}
			current = current->next;
		}
		if (i != 1)
			current->next = tmp;
	}
	else
		ev = tmp;
}

void	ft_order_env(t_infos *infos)
{
	t_env	*sorted = NULL;
	t_env	*current = infos->tmp_env;
	t_env	*next;
	t_env	*temp;

	while (current)
	{
		next = current->next;
		if (!sorted || ft_strcmp(current->name_folder, sorted->name_folder) < 0)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			temp = sorted;
			while (temp->next && ft_strcmp(temp->next->name_folder, current->name_folder) < 0)
			{
				temp = temp->next;
			}
			current->next = temp->next;
			temp->next = current;
		}
		current = next;
	}
	infos->tmp_env = sorted;
}

void	ft_print_order(t_infos *infos)
{
	t_env	*tmp;

	tmp = infos->tmp_env;
	while (tmp)
	{
		ft_printf("export %s=%s\n", tmp->name_folder, tmp->value_folder);
		tmp = tmp->next;
	}
}
