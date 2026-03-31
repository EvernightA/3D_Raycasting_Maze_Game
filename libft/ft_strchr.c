/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:33:16 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/19 11:11:31 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int c)
{
	int		i;
	char	*tmp;
	char	*point;

	i = 0;
	tmp = (char *)string;
	point = 0;
	if ((char)c == '\0')
	{
		point = &tmp[ft_strlen(string)];
		return (point);
	}
	while (tmp[i] != '\0')
	{
		if (tmp[i] == (char)c)
		{
			return (&tmp[i]);
		}
		i++;
	}
	return (point);
}
