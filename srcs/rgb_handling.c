/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:57:44 by mratsima          #+#    #+#             */
/*   Updated: 2025/09/25 17:12:19 by mratsima         ###   ########.fr       */
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
			ft_putstr_fd("Error\nWrong rgb value\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_rgb(t_rgb *rgb, char *og_rgb)
{
	char **split_rgb;
	char	*str_rgb;
	int	i;
	
	while (og_rgb[i])
	{
		if (og_rgb[i] == ',' && og_rgb[i + 1] == ',')
		{
			ft_putstr_fd("Error\nWrong rgb value\n", 2);
			return (1);	
		}
		i++;
	}
	i = 0;
	while (og_rgb[i] && !ft_isdigit(og_rgb[i]))
		i++;
	str_rgb = ft_strtrim(&og_rgb[i], " \t\n");
	split_rgb = ft_split(str_rgb, ',');
	if (!split_rgb
		|| (split_rgb && ((!split_rgb[0] && !split_rgb[1] && !split_rgb[2])
		|| split_rgb[3])))
	{
		ft_putstr_fd("Error\nWrong rgb value\n", 2);
		return (1);	
	}
	if (non_numeric_check(split_rgb[0]) || non_numeric_check(split_rgb[1])
		|| non_numeric_check(split_rgb[2]))
	{
		ft_putstr_fd("Error\nWrong rgb value\n", 2);
		return (1);	
	}
	if (atoll(split_rgb[0]) > 255 ||  atoll(split_rgb[1]) > 255 || atoll(split_rgb[2]) > 255
		|| atoll(split_rgb[0]) < 0 ||  atoll(split_rgb[1]) < 0 || atoll(split_rgb[2]) < 0)
	{
		ft_putstr_fd("Error\nWrong rgb value\n", 2);
		return (1);
	}	
	rgb->red = atoll(split_rgb[0]);
	rgb->green = atoll(split_rgb[1]);
	rgb->blue = atoll(split_rgb[2]);
	free(str_rgb);
	// printf("rgb = %d, %d, %d\n", rgb->red, rgb->green, rgb->blue);
	return (0);
}