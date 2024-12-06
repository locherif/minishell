/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locherif <locherif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:50:19 by locherif          #+#    #+#             */
/*   Updated: 2024/11/25 21:50:20 by locherif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_status(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == WORD)
		return (word_status(token->next));
	if (token->type == REDIR)
		return(redir_status(token->next));
	if(token->type == PIPE)
		return (pipe_status(token->next));
	return (1);
}
int	pipe_status(t_token *token)
{
	if (!token)
		return(0);
	if (token->type == WORD)
		return (word_status(token->next));
	if (token->type == PIPE)
		return (0);
	if (token->type == REDIR)
		return (redir_status(token->next));
	return(0);
}

int	redir_status(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == WORD)
		return (word_status(token->next));
	if (token->type == REDIR)
		return (0);
	if (token->type == PIPE)
		return (0);
	return (0);
}

int	start_status(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == REDIR)
		return (redir_status(token->next));
	if (token->type == WORD)
		return(word_status(token->next));
	return (0);
}

int	syntax_analysis(t_token *token)
{
	return(start_status(token));
}