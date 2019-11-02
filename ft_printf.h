/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:58:39 by akrache           #+#    #+#             */
/*   Updated: 2019/02/20 16:09:11 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# define HEX_L 49
# define HEX_U 17
# define CONV "cspdiouxX"
# define HH 1
# define H 2
# define L 3
# define LL 4

typedef struct			s_flag
{
	char	hex;
	char	sign;
	char	lmod;
	char	space;
	char	hash;
	char	zero;
	char	plus;
	char	minus;
	long	field;
	long	preci;
}						t_flag;

typedef struct			s_var
{
	int					count;
	t_flag				*flags;
	va_list				list;
	char				*args;
	int					argc;
	long long			argi;
	unsigned long long	argo;
	unsigned long long	argx;
	unsigned long long	argu;
	uintptr_t			argp;
}						t_var;

int						ft_printf(const char *format, ...);

void					ft_initflags(t_var *var);
void					ft_initvar(t_var *var);
int						ft_printf_flags(t_var *var, const char *format, int i);

void					ft_printf_c(t_var *var);
void					ft_printf_s(t_var *var);
void					ft_printf_di(t_var *var);
void					ft_printf_o(t_var *var);
void					ft_printf_x(t_var *var, char x);
void					ft_printf_u(t_var *var);
void					ft_printf_p(t_var *var);

void					ft_write_count(t_var *var, int fd, char *c, int len);
void					ft_write_ntimes(t_var *var, char c, int len);
void					ft_field_c(t_var *var);
int						ft_nb_digit(long long n);
int						ft_nb_digit_oct(unsigned long long n);
int						ft_nb_digit_hex(unsigned long long n);
int						ft_nb_digit_u(unsigned long long n);
void					*ft_memset(void *b, int c, size_t len);
char					*ft_strchr(char *s, int c);
int						ft_strlen(char *str);
int						ft_isdigit(int c);

#endif
