/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:52:58 by akrache           #+#    #+#             */
/*   Updated: 2019/02/20 16:37:55 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_preci_s(t_var *var, int len)
{
	if (var->flags->preci != -1 && len > 0)
		ft_write_count(var, 1, var->args, var->flags->preci);
	else
		ft_write_count(var, 1, var->args, len);
}

static void	ft_field_s(t_var *var, int pad)
{
	char	c;

	c = ' ';
	(var->flags->zero && !var->flags->minus ? c = '0' : 0);
	if (pad > 0)
		ft_write_ntimes(var, c, pad);
}

void		ft_printf_s(t_var *var)
{
	int len;
	int pad;

	var->args = va_arg(var->list, char *);
	if (!var->args)
		var->args = "(null)";
	len = ft_strlen(var->args);
	pad = var->flags->field - (var->flags->preci != -1
	&& var->flags->preci < len ? var->flags->preci : len);
	if (var->flags->minus)
	{
		ft_preci_s(var, len);
		if (var->flags->field)
			ft_field_s(var, pad);
	}
	else
	{
		if (var->flags->field)
			ft_field_s(var, pad);
		ft_preci_s(var, len);
	}
}

void		ft_field_c(t_var *var)
{
	int		pad;
	char	c;

	pad = var->flags->field - 1;
	c = ' ';
	(var->flags->zero && !var->flags->minus ? c = '0' : 0);
	if (pad > 0)
		ft_write_ntimes(var, c, pad);
}

void		ft_printf_c(t_var *var)
{
	unsigned char c;

	var->argc = va_arg(var->list, int);
	c = (unsigned char)var->argc;
	if (var->flags->minus)
	{
		write(1, &c, 1);
		if (var->flags->field)
			ft_field_c(var);
	}
	else
	{
		if (var->flags->field)
			ft_field_c(var);
		write(1, &c, 1);
	}
	var->count++;
}
