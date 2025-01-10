/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:16:30 by braugust          #+#    #+#             */
/*   Updated: 2024/06/05 14:45:03 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*b1;
	unsigned char	*b2;

	i = 0;
	b1 = (unsigned char *) s1;
	b2 = (unsigned char *) s2;
	while (b1[i] && b1[i] == b2[i] && n > 0)
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return (b1[i] - b2[i]);
}
