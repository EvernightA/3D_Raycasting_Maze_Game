/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:01:26 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/09/20 19:37:18 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	int		index;
	size_t	last;
	char	*new;
	int		len;

	i = 0;
	if (!s1)
		return (NULL);
	while (ft_is_in_set(s1[i], set))
		i++;
	last = ft_strlen (s1) - 1;
	while (ft_is_in_set(s1[last], set) && last != 0)
		last--;
	len = last - i + 1;
	if (len < 0)
		len = 0;
	new = (char *)malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	index = 0;
	while (index < len)
		new[index++] = s1[i++];
	new[index] = '\0';
	return (new);
}
