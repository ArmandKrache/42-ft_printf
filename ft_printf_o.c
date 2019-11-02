/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_o.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 17:46:38 by akrache           #+#    #+#             */
/*   Updated: 2019/02/20 15:47:00 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_printf_itoa_oct(t_var *var, unsigned long long n)
{
	char	*res;
	int		nb;

	(var->flags->lmod == 0 ? n = (unsigned int)n : 0);
	(var->flags->lmod == HH ? n = (unsigned char)n : 0);
	(var->flags->lmod == H ? n = (unsigned short int)n : 0);
	(var->flags->lmod == L ? n = (unsigned long int)n : 0);
	var->argo = n;
	nb = ft_nb_digit_oct(n);
	if (!(res = (char *)malloc(sizeof(char) * nb + 1)))
		return (NULL);
	res[nb] = '\0';
	while (--nb >= 0)
	{
		res[nb] = '0' + (n % 8);
		n = n / 8;
	}
	return (res);
}

static void	ft_field_o(t_var *var, char c, int pad, int pre)
{
	if (c == '0')
	{
		if (var->flags->hash && pre <= 0)
			ft_write_count(var, 1, "0", 1);
	}
	if (pad > 0)
		ft_write_ntimes(var, c, pad);
}

static void	ft_before_o(t_var *var, int pad, int pre)
{
	if (!var->flags->minus)
	{
		if (var->flags->preci == -1 && var->flags->zero)
			ft_field_o(var, '0', pad, pre);
		else
			ft_field_o(var, ' ', pad, pre);
	}
}

static void	ft_preci_o(t_var *var, int pre)
{
	if (!(var->flags->preci == -1 && var->flags->zero && !var->flags->minus))
	{
		if (var->flags->hash && pre <= 0)
			ft_write_count(var, 1, "0", 1);
	}
	if (pre > 0)
		ft_write_ntimes(var, '0', pre);
}

void		ft_printf_o(t_var *var)
{
	char	*str;
	int		pad;
	int		pre;

	var->argo = va_arg(var->list, unsigned long long);
	if (var->flags->preci == 0 && var->argo == 0)
		var->flags->field++;
	if (!(str = ft_printf_itoa_oct(var, var->argo)))
		return ;
	pre = var->flags->preci - ft_nb_digit_oct(var->argo);
	if (var->flags->hash && pre <= 0 && var->argo != 0)
		var->flags->field--;
	pad = var->flags->field - ft_nb_digit_oct(var->argo) - (pre > 0 ? pre : 0);
	ft_before_o(var, pad, pre);
	ft_preci_o(var, pre);
	if (!(var->flags->preci == 0 && var->argo == 0))
		ft_write_count(var, 1, str, ft_strlen(str));
	if (var->flags->minus)
		ft_field_o(var, ' ', pad, pre);
	free(str);
}
