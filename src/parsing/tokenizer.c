/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locherif <locherif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:50:26 by locherif          #+#    #+#             */
/*   Updated: 2024/11/25 21:50:27 by locherif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pipe(t_minishell *mini, int *i)
{
	t_token	*new_t;

	new_t = new_token(NULL, PIPE);
	if (!new_t)
		return (0);
	add_token_back(&(mini->token), new_t);
	(*i)++;
	return (1);
}

int	get_redir_double(t_minishell *mini, char *prompt, int *i)
{
	t_token	*new;
	char	*str;

	str = ft_substr(prompt, *i, 2);
	if (!str)
		return (0);
	new = new_token(str, REDIR);
	if (!new)
		return (free(str), 0);
	add_token_back(&(mini->token), new);
	(*i) += 2;
	return (1);
}

int	get_redir_simple(t_minishell *mini, char *prompt, int *i)
{
	t_token	*new;
	char	*str;

	str = ft_substr(prompt, *i, 1);
	if (!str)
		return (0);
	new = new_token(str, REDIR);
	if (!new)
		return (free(str), 0);
	add_token_back(&(mini->token), new);
	(*i)++;
	return (1);
}

int	get_word(char *prompt, t_minishell *mini, int *i)
{
	t_token	*new;
	char	*str;
	int		j;

	if (!prompt[*i])
		return (1);
	str = malloc(sizeof(char) * get_len_word(prompt, *i) + 1);
	if (!str)
		return (0);
	j = 0;
	while (prompt[*i] && !is_not_word(prompt[*i]))
	{
		if (prompt[*i] == '"' || prompt[*i] == '\'')
			add_between_quotes(str, prompt, &j, i);
		else
			str[j++] = prompt[(*i)++];
	}
	str[j] = 0;
	new = new_token(str, WORD);
	if (!new)
		return (free(str), 0);
	add_token_back(&(mini->token), new);
	return (1);
}

int	get_tokens(t_minishell *mini, char *prompt)
{
	int	i;
	int	added;

	i = 0;
	added = 1;
	while (prompt[i])
	{
		while (is_space(prompt[i]))
			i++;
		if (prompt[i] == '|')
			added = get_pipe(mini, &i);
		else if (!ft_strncmp(prompt + i, "<<", 2))
			added = get_redir_double(mini, prompt, &i);
		else if (!ft_strncmp(prompt + i, ">>", 2))
			added = get_redir_double(mini, prompt, &i);
		else if (!ft_strncmp(prompt + i, "<", 1))
			added = get_redir_simple(mini, prompt, &i);
		else if (!ft_strncmp(prompt + i, ">", 1))
			added = get_redir_simple(mini, prompt, &i);
		else
			added = get_word(prompt, mini, &i);
		if (!added)
			return (0);
	}
	return (1);
}

