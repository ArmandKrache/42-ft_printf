/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:55:38 by akrache           #+#    #+#             */
/*   Updated: 2019/02/20 14:19:39 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_write_count(t_var *var, int fd, char *c, int len)
{
	write(fd, c, len);
	var->count += len;
}

void	ft_write_ntimes(t_var *var, char c, int len)
{
	char *tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * len)))
		return ;
	ft_memset(tmp, c, len);
	ft_write_count(var, 1, tmp, len);
	free(tmp);
}

int		ft_nb_digit_oct(unsigned long long n)
{
	int	count;

	count = 1;
	while (n / 8 != 0)
	{
		n = n / 8;
		count++;
	}
	return (count);
}

int		ft_nb_digit_hex(unsigned long long n)
{
	int	count;

	count = 1;
	while (n / 16 != 0)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

int		ft_nb_digit_u(unsigned long long n)
{
	int	count;

	count = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}
