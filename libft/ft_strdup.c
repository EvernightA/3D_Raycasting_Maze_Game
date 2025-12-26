/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:21:39 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/26 09:42:17 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	char	*tmp;
	size_t	i;
	int		len;

	tmp = (char *)s;
	len = ft_strlen(tmp) + 1;
	new = (char *)malloc(len * sizeof(char));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(tmp))
	{
		new[i] = tmp[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
