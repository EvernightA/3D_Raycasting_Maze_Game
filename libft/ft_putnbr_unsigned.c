/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:58:00 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/27 10:19:08 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

void	ft_putnbr_unsigned(unsigned int nb)
{
	unsigned int	r;

	if (nb >= 10)
	{
		ft_putnbr_unsigned(nb / 10);
	}
	r = nb % 10 + '0';
	ft_putchar(r);
}
