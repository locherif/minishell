/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locherif <locherif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:43:21 by locherif          #+#    #+#             */
/*   Updated: 2024/12/06 20:25:33 by locherif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*

fd = open(redir->file, O_CREATE, O_APPEND);
if (fd < 0)
{
	error
}
dup2(0, fd);
close(fd);


*/

t_redir_type find_redir_type(char *redir_type)
{
	if (!ft_strncmp(redir_type, ">>", 2))
		return (APPEND);
	if (!ft_strncmp(redir_type, "<<", 2))
		return (HEREDOC);
	if (redir_type[0] == '<')
		return (IN);
	return (OUT);
}


void add_redir(t_redir *redirs, char *redir_type, char *file, int *i)
{
	redirs[*i].file = file;
	redirs[*i].type = find_redir_type(redir_type);
	(*i)++;
}

void	add_word(char **args, char *current_arg)
{
	int i;

	i = 0;
	while (args[i] != NULL)
		i++;
	args[i] = current_arg;
}
int	eclaireur(t_token *token, t_token_type type)
{
	int word;
	int	redir;
	
	word = 0;
	redir = 0;
	while(token && token->type != PIPE)
	{
		if(token->type == WORD)
			word++;
		if(token->type == REDIR)
		{
			redir++;
			token = token->next;
		}
		token = token->next;
	}
	if (type == WORD)
		return (word);
	return (redir);
}

int	ranger(t_token *token, t_minishell *minishell)
{
	t_command	*command;
	t_redir		*redirs;
	char 		**args;
	int i;
	
	while(token)
	{
		args = ft_calloc(eclaireur(token, WORD) + 1, sizeof(char *));
		redirs = ft_calloc(eclaireur(token, REDIR) + 1, sizeof(t_redir));
		if (!args || !redirs)
			return (free(args), free(redirs), 0);
		command = new_command(args, redirs);
		if (!command)
			return (free(args), free(redirs), 0);
		command->redir_size = eclaireur(token, REDIR);
		i = 0;
		while(token && token->type != PIPE)
		{
			if (token->type == WORD)
				add_word(args, ft_expand(token->content));
			else
			{
				add_redir(redirs, token->content, ft_expand(token->next->content), &i);
				token = token->next;
			}
			token = token->next;
		}
		add_command_back(&(minishell->command), command);
		if (token)
			token = token->next;
	}
	return (1);
}
