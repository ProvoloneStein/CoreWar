/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:51:31 by pstein            #+#    #+#             */
/*   Updated: 2020/02/27 19:43:37 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"
#include "op.h"

t_pars *parser_init()
{
	t_pars *pars;

	pars = (t_pars*)malloc(sizeof(t_pars));
	pars->comment = "This city needs me";
	pars->name = "Batman";
	pars->token = NULL;
	pars->mention = NULL;
	pars->code = ft_strnew(0);
	pars->line = 0;
	pars->column = 0;
	pars->code_size = 5;
	return(pars);
}

void make_tok(t_pars *parser)
{
    parser->token = (t_token*)malloc(sizeof(t_token));
    parser->token->type = INSTRUCTION;
    parser->token->content = "live";
    parser->token->next = (t_token*)malloc(sizeof(t_token));
    parser->token->next->type = DIRECT;
    parser->token->next->content = "1";
    parser->token->next->next = NULL;
}

int writing_in_file(t_pars *parser)
{
	int fd;
	char *bytecode;
	int i;
	int len;

	len = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4 + parser->code_size;
	i = 0;
	if ((fd = open("filename.cor", O_CREAT | O_WRONLY, 0644)) == -1)
		return(-1);
	if (!(bytecode = ft_strnew((size_t)parser->code_size)))
		return(-1);
	int_to_byte(bytecode, i, COREWAR_EXEC_MAGIC, 4);
	i += 4;
	ft_memcpy(&bytecode[i], parser->name, ft_strlen(parser->name));
	i += PROG_NAME_LENGTH;
	i += 4;
	int_to_byte(bytecode, i, parser->code_size, 4);
	i += 4;
	ft_memcpy(&bytecode[i], parser->comment, ft_strlen(parser->comment));
	i += COMMENT_LENGTH;
	i += 4;
	ft_memcpy(&bytecode[i], parser->code, parser->code_size);
	write(fd, bytecode, len);
	return(1);

}
int assembler(char *fd_map)
{
	t_pars *parser;
	char *kek = fd_map;

	ft_printf("%s", kek);
	if (!(parser = parser_init()))
		return(-1);
//	if (!(create_list(fd_map, parser)))
//		return(-1);  // прога в случае невалидного вода должна вылетать с ошибкой и показывать строчку и +- место в котором обнаружена ошибка/ внутри парсера должны быть заполнены токены и метки после твоей функции
	make_tok(parser);
//	read_tok(fd, parser);
	make_code(parser);
	writing_in_file(parser);
	return(1);
}

int is_s_file(char *str)
{
	int i;

	i = ft_strlen(str);
	if (i >= 3 && str[i - 2] == '.' && str[i - 1] == 's')
		return (1);
	return(0);	

}

int main(int argc, char **argv)
{
	if (argc == 2 && is_s_file(argv[1]))
		assembler(argv[1]);
	else
		ft_printf("usage: ./assembler map");
	return(0);	
}