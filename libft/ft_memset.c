/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:29:42 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/15 13:06:15 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*tmp;
	size_t			i;

	tmp = (unsigned char *)pointer;
	i = 0;
	while (i < count)
	{
		tmp[i] = value;
		i++;
	}
	return (pointer);
}
