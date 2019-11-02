/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:29:33 by akrache           #+#    #+#             */
/*   Updated: 2019/02/20 15:03:48 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_printf_itoa_hex(t_var *var, unsigned long long n)
{
	char	*res;
	int		nb;
	int		x;

	x = (var->flags->hex == 'x' ? HEX_L : HEX_U);
	(var->flags->lmod == 0 ? n = (unsigned int)n : 0);
	(var->flags->lmod == HH ? n = (unsigned char)n : 0);
	(var->flags->lmod == H ? n = (unsigned short int)n : 0);
	(var->flags->lmod == L ? n = (unsigned long int)n : 0);
	var->argx = n;
	nb = ft_nb_digit_hex(n);
	if (!(res = (char *)malloc(sizeof(char) * nb + 1)))
		return (NULL);
	res[nb] = '\0';
	while (--nb >= 0)
	{
		res[nb] = ('0' + (n % 16 >= 10 ? x + ((n % 16) % 10) : (n % 16)));
		n = n / 16;
	}
	return (res);
}

static void	ft_field_x(t_var *var, char c, int pad, int pre)
{
	(void)pre;
	if (c == '0')
	{
		if (var->flags->hash && var->argx != 0)
		{
			ft_write_count(var, 1, "0", 1);
			ft_write_count(var, 1, &var->flags->hex, 1);
		}
	}
	if (pad > 0)
		ft_write_ntimes(var, c, pad);
}

static void	ft_before_x(t_var *var, int pad, int pre)
{
	if (!var->flags->minus)
	{
		if (var->flags->preci == -1 && var->flags->zero)
			ft_field_x(var, '0', pad, pre);
		else
			ft_field_x(var, ' ', pad, pre);
	}
}

static void	ft_preci_x(t_var *var, int pre)
{
	if (!(var->flags->preci == -1 && var->flags->zero && !var->flags->minus))
	{
		if (var->flags->hash && var->argx != 0)
		{
			ft_write_count(var, 1, "0", 1);
			ft_write_count(var, 1, &var->flags->hex, 1);
		}
	}
	if (pre > 0)
		ft_write_ntimes(var, '0', pre);
}

void		ft_printf_x(t_var *var, char x)
{
	char	*str;
	int		pad;
	int		pre;

	var->flags->hex = x;
	var->argx = va_arg(var->list, unsigned long long);
	if (var->flags->preci == 0 && var->argx == 0)
		var->flags->field++;
	if (!(str = ft_printf_itoa_hex(var, var->argx)))
		return ;
	pre = var->flags->preci - ft_nb_digit_hex(var->argx);
	if (var->flags->hash && var->argx != 0)
		var->flags->field -= 2;
	pad = var->flags->field - ft_nb_digit_hex(var->argx) - (pre > 0 ? pre : 0);
	ft_before_x(var, pad, pre);
	ft_preci_x(var, pre);
	if (!(var->flags->preci == 0 && var->argx == 0))
		ft_write_count(var, 1, str, ft_strlen(str));
	if (var->flags->minus)
		ft_field_x(var, ' ', pad, pre);
	free(str);
}
