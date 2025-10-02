/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:31:11 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/10/02 22:33:19 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

size_t	find_len_max(char **map)
{
	int		i;
	size_t	max;

	i = 0;
	max = ft_strlen(map[i]);
	while (map[i])
	{
		if (max < ft_strlen(map[i]))
		{
			max = ft_strlen(map[i]);
		}
		i++;
	}
	return (max);
}
int map_invalid(int i, int j, int k, char **map)
{
	// check up and down 
	if ((map[i][k] == 'X' && (map[j][k] == '0' || is_player(map[j][k])))
	|| (map[j][k] == 'X' && (map[i][k] == '0' || is_player(map[i][k]))))
	{
		return (1);
	}
	// check up and dowwn
	if (((is_player(map[i][k]) && map[j][k] == 'X') || (is_player(map[j][k]) && map[i][k] == 'X'))
	|| ((is_player(map[j][k]) && map[j][k] == 'X') || (is_player(map[i][k]) && map[j][k] == 'X')))
	{
		return (1);
	}
	// check up and down
	if ((map[j][k] == ' ' && (map[i][k] == '0' || is_player(map[i][k])))
	|| (map[i][k] == ' ' && (map[j][k] == '0' || is_player(map[j][k])))
	)
	{
		return (1);
	}
	if (map[i][0] == '0')
	{
		return (1);
	}
	return (0);
}

char	*ft_strdup_x(char *s, int len)
{
	char		*new;
	char		*tmp;
	int			i;
	int 		j;

	tmp = (char *)s;
	new = (char *)ft_calloc(len + 2, sizeof(char));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (tmp[i] == '\n' || tmp[i] == '\0')
		{
			j = i;
			while (j < len - 1)
			{
				new[j] = 'X';
				j++;
			}
			new[j] = '\n';
			return (new);
		}
		else
		{
			new[i] = tmp[i];
		}
		i++;
	}
	new[i + 1] = '\0';
	return (new);
}

char	**dup_mat(int height, char **map)
{
	int 	i;
	char	**tmp;
	int		max_len;

	i = 0;
	tmp = (char **)ft_calloc(height + 2, sizeof(char *));
	if (!tmp)
		return (NULL);
	max_len = find_len_max(map);

	while (map[i])
	{
		tmp[i] = ft_strdup_x(map[i], max_len);
		i++;
	}
	return (tmp);
}
