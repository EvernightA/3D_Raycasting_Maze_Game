/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:27:59 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/27 12:11:51 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_count_number(int n);
void	ft_condition_all(const char *string, int *len, int *i, va_list list);
size_t	ft_count_unsigned(va_list list);
int		ft_putnbr_hex(va_list list, char type);
int		ft_print_memory(va_list list);
int		ft_putstr_and_len(va_list list, int fd);
void	ft_putnbr_unsigned(unsigned int nb);
int		ft_printf(const char *string, ...);
void	ft_putnbr(int nb);
void	ft_putchar(int c);

#endif
