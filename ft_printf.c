/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 13:57:54 by akrache           #+#    #+#             */
/*   Updated: 2019/02/20 16:29:39 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printf_none(t_var *var, const char *format, int i)
{
	if (var->flags->minus)
	{
		ft_write_count(var, 1, (char *)format + i, 1);
		if (var->flags->field)
			ft_field_c(var);
	}
	else
	{
		if (var->flags->field)
			ft_field_c(var);
		ft_write_count(var, 1, (char *)format + i, 1);
	}
}

static int	ft_printf_arg(t_var *var, const char *format, int i)
{
	ft_initflags(var);
	i = ft_printf_flags(var, format, i);
	if (format[i] == 'c')
		ft_printf_c(var);
	else if (format[i] == 's')
		ft_printf_s(var);
	else if (format[i] == 'd' || format[i] == 'i')
		ft_printf_di(var);
	else if (format[i] == 'o')
		ft_printf_o(var);
	else if (format[i] == 'x')
		ft_printf_x(var, 'x');
	else if (format[i] == 'X')
		ft_printf_x(var, 'X');
	else if (format[i] == 'u')
		ft_printf_u(var);
	else if (format[i] == 'p')
		ft_printf_p(var);
	else
		ft_printf_none(var, format, i);
	return (i);
}

static int	ft_printf_format(t_var *var, const char *format)
{
	int i;

	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '%')
			i = ft_printf_arg(var, format, i);
		else
		{
			if (format[i] == '%' && format[i + 1] == '%')
				i++;
			write(1, &format[i], 1);
			var->count++;
		}
		(format[i] ? i++ : 0);
	}
	return (i);
}

int			ft_printf(const char *format, ...)
{
	t_var	*var;
	int		res;

	if (!(var = (t_var *)malloc(sizeof(t_var))))
		return (-1);
	if (!(var->flags = (t_flag *)malloc(sizeof(t_flag))))
		return (-1);
	var->count = 0;
	ft_initvar(var);
	va_start(var->list, format);
	ft_printf_format(var, format);
	va_end(var->list);
	res = var->count;
	free(var->flags);
	free(var);
	return (res);
}
