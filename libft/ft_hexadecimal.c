/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 07:37:02 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/29 08:23:28 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

static void	print_number(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i != -1)
		ft_putchar(str[i--]);
}

int	ft_putnbr_hex(va_list list, char type)
{
	char			a[17];
	int				i;
	unsigned int	r;
	unsigned int	number;

	i = 0;
	number = va_arg(list, unsigned int);
	if (number == 0)
	{
		ft_putnbr(0);
		return (1);
	}
	while (number)
	{
		if (number % 16 <= 9)
			r = number % 16 + '0';
		else
			r = number % 16 + type - 10;
		number = number / 16;
		a[i] = r;
		i++;
	}
	a[i] = '\0';
	print_number(a);
	return (i);
}
