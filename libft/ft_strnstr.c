/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:29:05 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/15 17:14:08 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = -1;
	if (little[0] == '\0')
		return ((char *)&big[0]);
	while (++i < len && big[i] != '\0')
	{
		j = 0;
		if (big[i] == little[j])
		{
			while (little[j])
			{
				if (big[i + j] == little[j])
				{
					if ((j == ft_strlen(little) - 1) && i + j < len)
						return ((char *)&big[i]);
					j++;
				}
				else
					break ;
			}
		}
	}
	return (0);
}
