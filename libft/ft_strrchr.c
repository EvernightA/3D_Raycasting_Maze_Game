/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:47:58 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/15 13:16:49 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int s)
{
	int		i;
	char	*tmp;
	char	*point;

	while (s >= 256)
	{
		s = s - 256;
	}
	point = 0;
	tmp = (char *)string;
	i = (int)ft_strlen (tmp);
	while (i != -1)
	{
		if (tmp[i] == s)
		{
			return (&tmp[i]);
		}
		i--;
	}
	return (point);
}
