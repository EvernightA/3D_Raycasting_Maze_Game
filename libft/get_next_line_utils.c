/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 07:36:37 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/08/19 10:10:49 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	void			*ptr;
	size_t			multi;
	size_t			i;
	unsigned char	*str;

	multi = nmemb * size;
	if (multi != 0 && (multi / size) != nmemb)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	str = (unsigned char *)ptr;
	while (i < nmemb * size)
	{
		str[i] = '\0';
		i++;
	}
	return (ptr);
}

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		len1;
	int		len2;
	int		i;

	if (!s1)
		return (ft_strdup_gnl(s2));
	len1 = ft_strlen_gnl(s1);
	len2 = ft_strlen_gnl(s2);
	str = (char *)ft_calloc_gnl(len1 + len2 + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = -1;
	while (++i < len2 && s2[i])
		str[len1 + i] = s2[i];
	free(s1);
	return (str);
}

char	*ft_strdup_gnl(char *str)
{
	char	*new;
	int		i;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen_gnl(str) + 1;
	new = (char *)ft_calloc_gnl(len, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	return (new);
}

int	ft_is_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
