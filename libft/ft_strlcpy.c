/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:24:25 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/15 17:13:51 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len1;
	char	*tmp;

	tmp = (char *)src;
	len1 = ft_strlen(tmp);
	if (size == 0)
		return (len1);
	if (tmp[0] == '\0')
	{
		dst[0] = '\0';
		return (0);
	}
	i = 0;
	while (i < size - 1 && tmp[i] != '\0')
	{
		dst[i] = tmp[i];
		i++;
	}
	dst[i] = '\0';
	return (len1);
}
