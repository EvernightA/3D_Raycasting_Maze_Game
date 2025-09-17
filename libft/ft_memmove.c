/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:37:40 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/19 11:20:04 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp_d;
	unsigned char	*tmp_s;
	int				i;

	tmp_d = (unsigned char *)dest;
	tmp_s = (unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	if (dest < src)
	{
		ft_memcpy(dest, tmp_s, n);
		return (dest);
	}
	else
	{
		i = (int)n - 1;
		while (i != -1)
		{
			tmp_d[i] = tmp_s[i];
			i--;
		}
	}
	return (dest);
}
