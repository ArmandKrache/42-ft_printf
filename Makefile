# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akrache <akrache@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 15:30:18 by akrache           #+#    #+#              #
#    Updated: 2019/02/20 14:43:25 by akrache          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I ./

SRCS = ft_printf.c ft_printf_string.c structs.c ft_printf_int.c ft_utils.c \
		ft_printf_o.c ft_printf_x.c ft_printf_u.c ft_printf_p.c flags.c ft_utils2.c

OBJECT = $(SRCS:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJECT)
		$(CC) $(CFLAGS) -c $(SRCS)
		ar -rc $(NAME) $(OBJECT)
		ranlib $(NAME)

%.o: %.c ft_printf.h
	$(CC) -o $@ -c $< $(FLAGS)

clean:
	/bin/rm -rf $(OBJECT)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re