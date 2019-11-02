/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 18:29:08 by akrache           #+#    #+#             */
/*   Updated: 2019/02/20 14:07:28 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_initvar(t_var *var)
{
	var->count = 0;
	var->argc = 0;
	var->args = 0;
	var->argi = 0;
	var->argo = 0;
	var->argu = 0;
	var->argx = 0;
	var->argp = 0;
}

void	ft_initflags(t_var *var)
{
	var->flags->hex = 0;
	var->flags->sign = 1;
	var->flags->hash = 0;
	var->flags->minus = 0;
	var->flags->plus = 0;
	var->flags->space = 0;
	var->flags->zero = 0;
	var->flags->field = -1;
	var->flags->preci = -1;
	var->flags->lmod = 0;
}
