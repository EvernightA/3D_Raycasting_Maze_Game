/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:08:13 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/17 09:56:46 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*tmp;
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	tmp = (char *)src;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(tmp);
	i = 0;
	if (size <= len_dst)
		return (len_src + size);
	else
	{
		while (i < size - len_dst - 1 && tmp[i] != '\0')
		{
			dst[len_dst + i] = tmp[i];
			i++;
		}
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}
