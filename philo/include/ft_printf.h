/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:13:17 by afelger           #+#    #+#             */
/*   Updated: 2025/02/20 08:49:29 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf_set_fd(int fd);
int		ft_printf_get_fd(void);

int		ft_printf(const char *str, ...)__attribute__((format(printf, 1, 2)));
int		writeout_char(va_list ap);
int		writeout_string(va_list ap);
int		writeout_int(va_list ap);
int		writeout_uint(va_list ap);
int		writeout_pointer(va_list ap, const char *hex_string);
int		writeout_hex(va_list ap, const char *hex_string);

#endif /* FT_PRINTF_H */
