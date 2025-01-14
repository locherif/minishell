/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:04:36 by locherif          #+#    #+#             */
/*   Updated: 2025/01/14 08:32:38 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_quotes(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (!str[i])
				return (0);
		}
		i++;
	}
	return (1);
}

char	*match_token_type(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == REDIR)
		return ("REDIR");
	if (type == PIPE)
		return ("PIPE");
	return ("PIPE");
}

void	print_tokens(t_token *token)
{
	while (token)
	{
		if (token->type != PIPE)
			printf("name: %s, type: %s\n", token->content,
				match_token_type(token->type));
		else
			printf("name: PIPE, type: %s\n", match_token_type(token->type));
		token = token->next;
	}
}

void print_tab(char **tab)
{
	int i;

	if (!tab)
		return ;
	
	i = 0;
	printf("TAB\n");
	while (tab[i])
	{
		printf("%d : %s\n", i, tab[i]);
		i++;
	}
	
	return ;
}



char *match_redir_type(t_redir_type type)
{
	if (type == IN)
		return ("IN");

	if (type == OUT)
		return ("OUT");

	if (type == HEREDOC)
		return ("HEREDOC");

	return ("APPEND");
		
}

void	print_redirs(t_redir *redirs, int size)
{
	int i = 0;

	printf("REDIRS\n");
	while (i < size)
	{
		printf("Type = %s, File = %s\n", match_redir_type(redirs[i].type), redirs[i].file);
		i++;
	}
}

void	print_commands(t_command *command)
{
	int i = 0;
	while(command)
	{
		printf("COMMAND number %d: \n", i);
		print_tab(command->args);
		print_redirs(command->redirs, command->redir_size);
		command = command->next;
		i++;
		printf("\n\n");
	}
}

void	expand_test(t_minishell *minishell)
{
	t_command	*cmd_check;
	int			i;
	
	printf("----- DEBUG AFTER EXPAND -----\n");
	cmd_check = minishell->command;
	while (cmd_check)
	{
    	printf("Commande:\n");
    	i = 0;
   		while (cmd_check->args && cmd_check->args[i])
    	{
       		printf("Arg[%d] = '%s'\n", i, cmd_check->args[i]);
        	i++;
    	}
    cmd_check = cmd_check->next;
	}
	printf("--------------------------------\n");
}

bool	parsing(char *str, t_minishell *minishell)
{
	minishell->token = NULL;
	minishell->command = NULL;
	if (!check_quotes(str))
		return (0);
	if (!get_tokens(minishell, str))
		return (clear_token(minishell->token), 0);
	//print_tokens(minishell->token);
	if (!syntax_analysis(minishell->token))
		return (printf("c guez\n"), clear_token(minishell->token), 0);
	if (!ranger(minishell->token, minishell))
		return (printf("nul"), 0);
	print_commands(minishell->command);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{	
	t_minishell	minishell;
	char		*str;

	(void)argc;
	(void)argv;
	minishell = (t_minishell){0};
	minishell.env_list = init_env_list(envp);
	//print_env_list(minishell.env_list);
	if (!minishell.env_list)
		return (1);
	while (1)
	{
		str = readline(">😜 ");
		if (!str)
			break ;
		if (!*str)
			continue ;
		add_history(str);
		if (!parsing(str, &minishell))
		{
			free(str);
			continue;
		}
		expand_var_command(minishell.command, minishell.shell.exit_status, minishell.env_list);
		//expand_test(&minishell);
		free(str);
		clear_token(minishell.token);
		clear_command(minishell.command);
	}
	return (0);
}

