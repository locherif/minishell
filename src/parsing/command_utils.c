/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locherif <locherif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:50:10 by locherif          #+#    #+#             */
/*   Updated: 2024/12/08 19:27:20 by locherif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_command(char **args, t_redir *redirs)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->args = args;
	command->redirs = redirs;
	command->next = NULL;
	return (command);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	clear_command(t_command *command)
{
	t_command	*tmp;

	while (command)
	{
		tmp = command->next;
		// free_tab(command->args);
		free(command->args);
		free(command->redirs);
		free(command);
		command = tmp;
	}
}

t_command	*last_command(t_command *command)
{
	while (command->next)
		command = command->next;
	return (command);
}

void	add_command_back(t_command **command_list, t_command *new_element)
{
	t_command	*last;

	if (!command_list)
		return ;
	if (!(*command_list))
		*command_list = new_element;
	else
	{
		last = last_command((*command_list));
		last->next = new_element;
	}
}
