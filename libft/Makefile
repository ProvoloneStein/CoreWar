# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 17:48:56 by gwyman-m          #+#    #+#              #
#    Updated: 2020/06/01 12:46:55 by sts              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

PRINTFSRC_DIR = printf/

LIBFTSRC_DIR = srcs/

FLAGS = -Wall -Wextra -Werror -c -I.

HEADER = libft.h

HEADER_PRINTF = ft_printf.h

CLIBFT= ft_bzero.c			ft_memccpy.c		ft_memchr.c\
		ft_memcmp.c			ft_memcpy.c			ft_memset.c\
		ft_strdup.c			ft_strlen.c			ft_putchar.c\
		ft_putstr.c			ft_strcpy.c			ft_strcat.c\
		ft_atoi.c			ft_isalnum.c		ft_isalpha.c\
		ft_isascii.c		ft_isdigit.c		ft_memalloc.c\
		ft_isprint.c		ft_strchr.c			ft_strncpy.c\
		ft_strnstr.c		ft_strrchr.c		ft_strstr.c\
		ft_tolower.c		ft_toupper.c\
		ft_putnbr.c\
		ft_strcmp.c			ft_memmove.c		ft_strncmp.c\
		ft_strncat.c		ft_strlcat.c		ft_memdel.c\
		ft_strnew.c			ft_strclr.c			ft_striter.c\
		ft_striteri.c		ft_strequ.c			ft_strnequ.c\
		ft_strsub.c			ft_strjoin.c		ft_strtrim.c\
		ft_strsplit.c		ft_itoa.c			ft_putendl.c\
		ft_putchar_fd.c		ft_putstr_fd.c		ft_putendl_fd.c\
		ft_putnbr_fd.c		ft_strmap.c			ft_strmapi.c\
		ft_lstnew.c			ft_lstadd.c			ft_lstdelone.c\
		ft_lstdel.c			ft_lstiter.c		ft_lstmap.c\
		ft_strdel.c			get_next_line.c


CPRINTF= ft_printf.c checker.c colors.c display.c\
		flags.c ld_1.c ld_2.c ld_3.c ld_4.c\
		libft_modf.c libft_modf2.c ft_itoa_bpf.c\
		long_doudle.c maxnbr.c num_str.c num_str2.c\
		take_str.c take_str2.c

LIBFTSRC = $(addprefix $(LIBFTSRC_DIR),$(CLIBFT))

PRINTFSRC = $(addprefix $(PRINTFSRC_DIR),$(CPRINTF))

CFILES = $(PRINTFSRC) $(LIBFTSRC)

OFILES = $(LIBFTSRC:%.c=%.o) $(PRINTFSRC:%.c=%.o)

VPATH := printf:srcs

all: $(NAME)

$(NAME): $(OFILES)
	@ar rc libft.a $(OFILES)
	@ranlib libft.a
	@printf "\r\033[0;32m.o files are ready                      \033[0m\n"
	@printf "\e[?25h\033[0;32mlibft.a is ready\033[0m\n"

srcs/%.o: %.c $(HEADER)
	@gcc $(FLAGS) $< -o $@
	@printf "\e[?25l\033[0;33mcompiling $<\033[0m\033\r"
	@printf "                                 \r"

printf/%.o: %.c $(HEADER_PRINTF)
	@gcc $(FLAGS) $< -o $@
	@printf "\e[?25l\033[0;33mcompiling $<\033[0m\033\r"
	@printf "                                 \r"

clean:
	@rm -f $(OFILES)
	@echo "\033[0;31mthe libft directory is cleaned\033[0m"

fclean: clean
	@rm -f libft.a
	@echo "\033[0;31mdeleted libft.a\033[0m"

re: fclean all
