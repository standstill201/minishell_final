# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 13:18:01 by seokjyoo          #+#    #+#              #
#    Updated: 2023/02/08 11:14:07 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

CC		= gcc
CFLAG	= -Wall -Wextra -Werror

RM		= rm -f

SRC_1	= ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_iswhite.c \

SRC_2	= ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstmap.c \
	ft_lstiter.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstadd_back.c \
	ft_lstlast.c \
	ft_lstsize.c \
	ft_lstadd_front.c \
	ft_lstnew.c \

SRCS	=	$(SRC_1) \
			$(SRC_2) \

OBJS	=	$(SRCS:.c=.o)

all	:	$(NAME)

%.o		: %.c
		$(CC) $(CFLAG) -c $< -o $@

clean	:
		$(RM) $(OBJS)

fclean	: clean
		$(RM) $(NAME)

re	: fclean all

$(NAME)	: $(OBJS)
		ar -cr $@ $^

.PHONY	: all clean fclean bonus
