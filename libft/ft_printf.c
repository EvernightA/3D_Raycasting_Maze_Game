/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:59:50 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/27 14:46:35 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_affectation(int *a, int *b)
{
	*a = -1;
	*b = 0;
}

static void	ft_percent(int *len, int *i)
{
	ft_putchar('%');
	*len = *len + 1 - 2;
	(*i)++;
}

static void	ft_check_converter(const char *string, int *i, int *len,
		va_list list)
{
	(*i)++;
	if (string[*i] == '%')
		ft_percent(len, i);
	else
	{
		ft_condition_all(string, len, i, list);
		(*i)++;
	}
}

int	ft_printf(const char *string, ...)
{
	va_list	list;
	int		i;
	int		len;

	va_start(list, string);
	ft_affectation(&i, &len);
	while (string[++i] != '\0')
	{
		if (string[i] == '%')
			ft_check_converter(string, &i, &len, list);
		if (string[i] != '\0')
		{
			if (string[i] == '%')
			{
				i--;
				continue ;
			}
			ft_putchar(string[i]);
		}
		else
			break ;
	}
	va_end(list);
	return (i + len);
}
