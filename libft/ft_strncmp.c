/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:28:25 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/09/20 13:14:16 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;

	i = 0;
	tmp_s1 = (unsigned char *) s1;
	tmp_s2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (i < n - 1 && (tmp_s1[i] != '\0' || tmp_s2[i] != '\0'))
	{
		if (tmp_s1[i] != tmp_s2[i])
		{
			return (tmp_s1[i] - tmp_s2[i]);
		}
		i++;
	}
	return (tmp_s1[i] - tmp_s2[i]);
}
