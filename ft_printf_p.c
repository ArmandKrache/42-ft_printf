/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:56:46 by akrache           #+#    #+#             */
/*   Updated: 2019/02/20 14:32:43 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_field_p(t_var *var, char c, int pad, int pre)
{
	(void)pre;
	if (c == '0')
		ft_write_count(var, 1, "0x", 2);
	if (pad > 0)
		ft_write_ntimes(var, c, pad);
}

static void	ft_before_p(t_var *var, int pad, int pre)
{
	if (!var->flags->minus)
	{
		if (var->flags->preci == -1 && var->flags->zero)
			ft_field_p(var, '0', pad, pre);
		else
			ft_field_p(var, ' ', pad, pre);
	}
}

static void	ft_preci_p(t_var *var, int pre)
{
	if (!(var->flags->preci == -1 && var->flags->zero && !var->flags->minus))
		ft_write_count(var, 1, "0x", 2);
	if (pre > 0)
		ft_write_ntimes(var, '0', pre);
}

static char	*ft_printf_itoa_p(uintptr_t n)
{
	char	*res;
	int		nb;

	nb = ft_nb_digit_hex(n);
	if (!(res = (char *)malloc(sizeof(char) * nb + 1)))
		return (NULL);
	res[nb] = '\0';
	while (--nb >= 0)
	{
		res[nb] = ('0' + (n % 16 >= 10 ? HEX_L + ((n % 16) % 10) : (n % 16)));
		n = n / 16;
	}
	return (res);
}

void		ft_printf_p(t_var *var)
{
	char	*str;
	int		pad;
	int		pre;

	var->flags->hex = 'x';
	var->argp = va_arg(var->list, uintptr_t);
	if (var->flags->preci == 0 && var->argp == 0)
		var->flags->field++;
	if (!(str = ft_printf_itoa_p(var->argp)))
		return ;
	pre = var->flags->preci - ft_nb_digit_hex(var->argp);
	var->flags->field -= 2;
	pad = var->flags->field - ft_nb_digit_hex(var->argp) - (pre > 0 ? pre : 0);
	ft_before_p(var, pad, pre);
	ft_preci_p(var, pre);
	if (!(var->flags->preci == 0 && var->argp == 0))
		ft_write_count(var, 1, str, ft_strlen(str));
	if (var->flags->minus)
		ft_field_p(var, ' ', pad, pre);
	free(str);
}
