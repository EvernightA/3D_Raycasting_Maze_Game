/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:48:29 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/17 15:20:26 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_count_word(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] != c && str[i] != '\0')
			count++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (count);
}

static int	ft_len_word(char const *str, char c, int *i)
{
	int	len;

	while (str[*i] == c && str[*i])
		(*i)++;
	len = 0;
	while (str[*i] != c && str[*i])
	{
		len++;
		(*i)++;
	}
	return (len);
}

static char	**ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static char	*ft_affectation(char const *s, char c, int l_word, int j)
{
	int		i;
	char	*str;

	str = (char *)ft_calloc(l_word, sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[j] == c && s[j])
		j++;
	i = 0;
	while (i < l_word - 1)
	{
		str[i] = s[j + i];
		i++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		i;
	int		j;
	int		len;
	int		tmp;

	new = (char **)ft_calloc(ft_count_word(s, c) + 1, sizeof(char *));
	if (new == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_count_word(s, c) && s[j] != '\0')
	{
		tmp = j;
		len = ft_len_word(s, c, &j);
		new[i] = ft_affectation(s, c, len + 1, tmp);
		if (new[i] == NULL)
			return (ft_free(new));
		i++;
	}
	return (new);
}
