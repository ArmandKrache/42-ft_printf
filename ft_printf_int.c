/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:12:35 by akrache           #+#    #+#             */
/*   Updated: 2019/02/20 14:33:37 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_printf_itoa(t_var *var, long long n)
{
	char	*res;
	int		nb;

	(var->flags->lmod == 0 ? n = (int)n : 0);
	(var->flags->lmod == HH ? n = (char)n : 0);
	(var->flags->lmod == H ? n = (short int)n : 0);
	(var->flags->lmod == L ? n = (long int)n : 0);
	var->argi = n;
	nb = ft_nb_digit(n);
	if (n < 0)
		var->flags->sign = -1;
	if (!(res = (char *)malloc(sizeof(char) * nb + 1)))
		return (NULL);
	res[nb] = '\0';
	while (--nb >= 0)
	{
		res[nb] = '0' + (n % 10) * var->flags->sign;
		n = n / 10;
	}
	return (res);
}

static void	ft_field_di(t_var *var, char c, int pad)
{
	if (c == '0')
	{
		if (var->flags->sign < 0)
			ft_write_count(var, 1, "-", 1);
		else if (var->flags->plus)
			ft_write_count(var, 1, "+", 1);
	}
	if (pad > 0)
		ft_write_ntimes(var, c, pad);
}

static void	ft_before_di(t_var *var, int pad)
{
	if (var->flags->space && var->flags->sign == 1 && !var->flags->plus)
		ft_write_count(var, 1, " ", 1);
	if (!var->flags->minus)
	{
		if (var->flags->preci == -1 && var->flags->zero)
			ft_field_di(var, '0', pad);
		else
			ft_field_di(var, ' ', pad);
	}
}

static void	ft_preci_di(t_var *var, int pre)
{
	if (!(var->flags->preci == -1 && var->flags->zero && !var->flags->minus))
	{
		if (var->flags->sign < 0)
			ft_write_count(var, 1, "-", 1);
		else if (var->flags->plus)
			ft_write_count(var, 1, "+", 1);
	}
	if (pre > 0)
		ft_write_ntimes(var, '0', pre);
}

void		ft_printf_di(t_var *var)
{
	char	*str;
	int		pad;
	int		pre;

	var->argi = va_arg(var->list, long long);
	if (var->flags->preci == 0 && var->argi == 0)
		var->flags->field++;
	if (!(str = ft_printf_itoa(var, var->argi)))
		return ;
	if ((var->flags->plus || var->flags->space || var->flags->sign == -1))
		var->flags->field--;
	pre = var->flags->preci - ft_nb_digit(var->argi);
	pad = var->flags->field - ft_nb_digit(var->argi) - (pre > 0 ? pre : 0);
	ft_before_di(var, pad);
	ft_preci_di(var, pre);
	if (!(var->flags->preci == 0 && var->argi == 0))
		ft_write_count(var, 1, str, ft_strlen(str));
	if (var->flags->minus)
		ft_field_di(var, ' ', pad);
	free(str);
}
