# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pstein <pstein@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/27 16:25:48 by pstein            #+#    #+#              #
#    Updated: 2020/02/27 19:06:18 by pstein           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN = lem-in

FLAGS = -Wall -Wextra -Werror -I. -I ./libft/srcs -I ./libft/printf

LIB = -L libft/ -lft

LEM_IN_SRC_DIR= srcs/

HEADER= assem.h

CLEM_IN= main.c functions.c read_struckt.c funct1.c funct2.c funct3.c funct4.c 

LEM_IN_SRC = $(addprefix $(LEM_IN_SRC_DIR),$(CLEM_IN))

LEM_IN_OBJ = $(LEM_IN_SRC:%.c=%.o)

.PHONY: all clean fclean re

all: $(LEM_IN)

$(LEM_IN): $(LEM_IN_OBJ) $(HEADER)
	make -C libft
	gcc $(FLAGS) $(LEM_IN_OBJ) -o $(LEM_IN) $(LIB)

$(LEM_IN_SRC_DIR)%.o : $(LEM_IN_SRC_DIR)%.c $(HEADER)
	gcc -c $(FLAGS) $< -o $@

clean:	
	@rm -f $(LEM_IN_OBJ)
fclean: clean	
	make fclean -C libft/	
	rm -fv $(LEM_IN)

re: fclean all
