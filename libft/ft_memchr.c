/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:45:15 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/19 08:18:51 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	size_t			i;
	unsigned char	*point;
	unsigned char	new_c;

	tmp = (unsigned char *)s;
	new_c = (unsigned char)c;
	i = 0;
	point = 0;
	while (i < n)
	{
		if (tmp[i] == new_c)
		{
			point = &tmp[i];
			return (point);
		}
		i++;
	}
	return (NULL);
}
