/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:50:16 by locherif          #+#    #+#             */
/*   Updated: 2025/01/28 09:41:09 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_space(char c)
{
	if ((c == ' ') || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
int	is_not_word(char c)
{
	if (is_space(c) || c == '>' || c == '<' ||c == '|')
		return (1);
	return (0);
}

int	get_len_word(char *prompt, int i)
{
	int		len;
	char	quote;

	len = 0;
	while (prompt[i] && !is_not_word(prompt[i]))
	{
		if (prompt[i] == '"' || prompt[i] == '\'')
		{
			quote = prompt[i];
			len++;
			while (prompt[++i] != quote)
			{
				len++;
			}
			len++;
		}
		len++;
		i++;
	}
	return (len);
}

void	add_between_quotes(char *str, char *input, int *j, int *i)
{
	char	quote;

	quote = input[(*i)++];
	str[(*j)++] = quote;
	while (input[*i] != quote)
		str[(*j)++] = input[(*i)++];
	str[(*j)++] = input[(*i)++];
}