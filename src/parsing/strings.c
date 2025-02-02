/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:50:13 by locherif          #+#    #+#             */
/*   Updated: 2025/01/14 08:19:21 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	if (!n)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}

// char	*ft_substr(char *s, unsigned int start, int len)
// {
// 	char	*str;
// 	int		i;
// 	int		j;
// 	int		size;

// 	if (s == NULL)
// 		return (NULL);
// 	if (len > ft_strlen(s))
// 		size = ft_strlen(s + start);
// 	else
// 		size = len;
// 	str = malloc(sizeof(char) * (size + 1));
// 	if (!str)
// 		return (NULL);
// 	i = start;
// 	j = 0;
// 	while (s[i] && j < len)
// 		str[j++] = s[i++];
// 	str[j] = 0;
// 	return (str);
// }