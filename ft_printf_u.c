/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 19:38:23 by akrache           #+#    #+#             */
/*   Updated: 2019/02/20 14:32:54 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_printf_itoa_u(t_var *var, unsigned long long n)
{
	char	*res;
	int		nb;

	(var->flags->lmod == 0 ? n = (unsigned int)n : 0);
	(var->flags->lmod == HH ? n = (unsigned char)n : 0);
	(var->flags->lmod == H ? n = (unsigned short int)n : 0);
	(var->flags->lmod == L ? n = (unsigned long int)n : 0);
	var->argu = n;
	nb = ft_nb_digit_u(n);
	if (!(res = (char *)malloc(sizeof(char) * nb + 1)))
		return (NULL);
	res[nb] = '\0';
	while (--nb >= 0)
	{
		res[nb] = '0' + (n % 10);
		n = n / 10;
	}
	return (res);
}

static void	ft_field_u(t_var *var, char c, int pad)
{
	if (pad > 0)
		ft_write_ntimes(var, c, pad);
}

static void	ft_before_u(t_var *var, int pad)
{
	if (!var->flags->minus)
	{
		if (var->flags->preci == -1 && var->flags->zero)
			ft_field_u(var, '0', pad);
		else
			ft_field_u(var, ' ', pad);
	}
}

static void	ft_preci_u(t_var *var, int pre)
{
	if (pre > 0)
		ft_write_ntimes(var, '0', pre);
}

void		ft_printf_u(t_var *var)
{
	char	*str;
	int		pad;
	int		pre;

	var->argu = va_arg(var->list, unsigned long long);
	if (var->flags->preci == 0 && var->argu == 0)
		var->flags->field++;
	if (!(str = ft_printf_itoa_u(var, var->argu)))
		return ;
	pre = var->flags->preci - ft_nb_digit_u(var->argu);
	pad = var->flags->field - ft_nb_digit_u(var->argu) - (pre > 0 ? pre : 0);
	ft_before_u(var, pad);
	ft_preci_u(var, pre);
	if (!(var->flags->preci == 0 && var->argu == 0))
		ft_write_count(var, 1, str, ft_strlen(str));
	if (var->flags->minus)
		ft_field_u(var, ' ', pad);
	free(str);
}
