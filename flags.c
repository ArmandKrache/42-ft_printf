/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:41:48 by akrache           #+#    #+#             */
/*   Updated: 2019/02/20 15:53:23 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_precision(t_var *var, const char *format, int i)
{
	long res;

	res = 0;
	if (format[++i] == '-')
		;
	else
	{
		while (ft_isdigit(format[i]))
		{
			res *= 10;
			res += format[i] - '0';
			i++;
		}
	}
	var->flags->preci = res;
	return (--i);
}

static int	ft_get_field(t_var *var, const char *format, int i)
{
	long res;

	res = 0;
	while (ft_isdigit(format[i]))
	{
		res *= 10;
		res += format[i] - '0';
		i++;
	}
	var->flags->field = res;
	return (--i);
}

static int	ft_get_length(t_var *var, const char *format, int i)
{
	if (format[i] == 'h' && format[i + 1] == 'h')
	{
		var->flags->lmod = HH;
		i++;
	}
	else if (format[i] == 'h' && format[i + 1] != 'h')
		var->flags->lmod = H;
	else if (format[i] == 'l' && format[i + 1] != 'l')
		var->flags->lmod = L;
	else if (format[i] == 'l' && format[i + 1] == 'l')
	{
		var->flags->lmod = LL;
		i++;
	}
	return (i);
}

int			ft_printf_flags(t_var *var, const char *format, int i)
{
	while (format[++i] && !(ft_strchr(CONV, format[i])))
	{
		if (format[i] == '#')
			var->flags->hash = 1;
		else if (format[i] == ' ')
			var->flags->space = 1;
		else if (format[i] == '-')
			var->flags->minus = 1;
		else if (format[i] == '+')
			var->flags->plus = 1;
		else if (format[i] == '0')
			var->flags->zero = 1;
		else if (format[i] == '.')
			i = ft_get_precision(var, format, i);
		else if (format[i] >= '1' && format[i] <= '9')
			i = ft_get_field(var, format, i);
		else if (format[i] == 'h' || format[i] == 'l')
			i = ft_get_length(var, format, i);
		else
			break ;
	}
	return (i);
}
