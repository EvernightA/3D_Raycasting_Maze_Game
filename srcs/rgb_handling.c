/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:57:44 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/08 11:35:04 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	non_numeric_check(char *rgb_part)
{
	int	i;

	i = 0;
	while (rgb_part[i])
	{
		if (!ft_isdigit(rgb_part[i]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	successive_commas(int *i, char *og_rgb)
{
	while (og_rgb[*i])
	{
		if (og_rgb[*i] == ',' && og_rgb[(*i) + 1] == ',')
		{
			ft_putstr_fd("Error\nWrong rgb value(successive commas)\n", 2);
			return (1);
		}
		(*i)++;
	}
	return (0);
}

int	not_enough_values(char **split_rgb)
{
	return (!split_rgb || (split_rgb && ((!split_rgb[0] && !split_rgb[1]
					&& !split_rgb[2]) || split_rgb[3])));
}

int	non_numeric_values(char **split_rgb)
{
	return (non_numeric_check(split_rgb[0]) || non_numeric_check(split_rgb[1])
		|| non_numeric_check(split_rgb[2]));
}

int	overflowing_values(char **split_rgb)
{
	return (ft_atoll(split_rgb[0]) > 255 || ft_atoll(split_rgb[1]) > 255
		|| ft_atoll(split_rgb[2]) > 255 || ft_atoll(split_rgb[0]) < 0
		|| ft_atoll(split_rgb[1]) < 0 || ft_atoll(split_rgb[2]) < 0);
}

int	get_rgb(t_rgb *rgb, char *og_rgb)
{
	char	**split_rgb;
	char	*str_rgb;
	int		i;

	i = 0;
	if (successive_commas(&i, og_rgb))
		return (1);
	i = 0;
	while (og_rgb[i] && !ft_isdigit(og_rgb[i]))
		i++;
	str_rgb = ft_strtrim(&og_rgb[i], " \t\n");
	split_rgb = ft_split(str_rgb, ',');
	if (not_enough_values(split_rgb) || non_numeric_values(split_rgb)
		|| overflowing_values(split_rgb))
	{
		free(str_rgb);
		free_split(split_rgb);
		ft_putstr_fd("Error\nWrong rgb value\n", 2);
		return (1);
	}
	rgb->red = ft_atoll(split_rgb[0]);
	rgb->green = ft_atoll(split_rgb[1]);
	rgb->blue = ft_atoll(split_rgb[2]);
	free(str_rgb);
	free_split(split_rgb);
	return (0);
}
