# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pstein <pstein@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/27 16:25:48 by pstein            #+#    #+#              #
#    Updated: 2020/03/14 15:29:32 by pstein           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm

FLAGS = -Wall -Wextra -Werror -I. -I ./libft/srcs -I ./libft/printf

LIB = -L libft/ -lft

ASM_SRC_DIR= srcs/

DASM_SRC_DIR= src1/

HEADER= assem.h

HEADERS_DIRECTORY= includes/

ASM_HEADERS_LIST = \
	op.h\
	assem.h\
	disassem.h\

ASM_HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(ASM_HEADERS_LIST))

C_ASM= main.c functions.c read_struct.c funct1.c funct2.c funct3.c funct4.c create_list.c checks.c operations.c variables.c functions2.c read_commands.c errors.c code_generator.c checks2.c edgar_func.c edgar_func1.c

C_DASM= d_func.c d_func1.c d_func2.c d_func3.c d_func4.c reader.c disassembler.c

ASM_SRC = $(addprefix $(ASM_SRC_DIR),$(C_ASM))

ASM_SRC += $(addprefix $(DASM_SRC_DIR),$(C_DASM))

ASM_OBJ = $(ASM_SRC:%.c=%.o)

.PHONY: all clean fclean re

all: $(ASM)

$(ASM): $(ASM_OBJ) $(ASM_HEADERS) 
	make -C libft
	gcc $(FLAGS) $(ASM_OBJ) -o $(ASM) $(LIB)

$(ASM_SRC_DIR)%.o : $(ASM_SRC_DIR)%.c $(ASM_HEADERS) 
	gcc -c $(FLAGS) $< -o $@

clean:	
	@rm -f $(ASM_OBJ)
fclean: clean	
	make fclean -C libft/	
	rm -fv $(ASM)

re: fclean all
