/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locherif <locherif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:50:10 by locherif          #+#    #+#             */
/*   Updated: 2024/11/25 21:50:11 by locherif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *str, t_token_type type)
{

	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return(NULL);
	token->content = str;
	token->type = type;
	token->next = NULL;
	return (token);
}
 
void	clear_token(t_token *token)
{
	t_token	*tmp;
	while (token)
	{
		tmp = token->next;
		if (token->type != PIPE)
			free(token->content);
		free(token);
		token = tmp; 
	}
}
  
t_token	*last_token(t_token *token)
{
	while (token->next)
		token = token->next;
	return (token);
}

void	add_token_back(t_token **token_list, t_token *new_element)
{
	t_token *last;

	if (!token_list)
		return ;
	if (!(*token_list))
		*token_list = new_element;
	else
	{
		last = last_token((*token_list));
		last->next = new_element;
	}
} 
