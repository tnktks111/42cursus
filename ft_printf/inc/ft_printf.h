/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:35:48 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/05 12:35:49 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

// utils
int		ft_print_addr(void *ptr, int *cnt);
int		ft_print_hex(unsigned int un, int islower, int *cnt);
int		f_ptr_parser(char format, void *arg);
int		f_int_parser(char format, int arg);

// libft_for_ft_printf
int		ft_putchar(char c);
int		ft_putnbr_and_len(int n, int *cnt);
int		ft_putunbr_and_len(unsigned int un, int *cnt);
int		ft_putstr_and_len(char *s);
size_t	ft_strlen(const char *s);

int		format_parser(va_list args, char format);
int		ft_printf(const char *format, ...);

#endif