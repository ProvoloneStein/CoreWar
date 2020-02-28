#include "assem.h"
#include "op.h"
#include "stdlib.h"
#include "stdio.h"
void	int_to_byte(char *data,
							int32_t pos,
							int32_t value,
							size_t size)
{
	int8_t		i;

	i = 0;
	while (size)
	{
		data[pos + size - 1] = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

void neg_to_byte(char *data, int32_t pos, int32_t value, size_t size)
{
	int8_t		i;

	i = 0;
	while (size - 1 > 0)
	{
		data[pos + size - 1] = (uint8_t)((value >> i) & 0x00);
		i += 8;
		size--;
	}
    data[pos + size - 1] = (uint8_t)((value >> i) & 0x00) + (uint8_t)(1 >> i);
}

t_pars *parser_init()
{
	t_pars *pars;

	pars = (t_pars*)malloc(sizeof(t_pars));
	pars->comment = NULL;
	pars->name = NULL;
	pars->line = 0;
	pars->column = 0;
	return(pars);
}

void make_tok(t_pars *parser)
{
    parser->token = (t_token*)malloc(sizeof(t_token));
    parser->token->type = LABEL;
    parser->token->content = "live";
    parser->token->next = (t_token*)malloc(sizeof(t_token));
    parser->token->next->type = DIRECT;
    parser->token->next->content = "1";
    parser->token->next->next = NULL;
}

char *assembler(t_pars *parser)
{
	make_tok(parser);
//	read_tok(fd, parser);
	ft_printf("%s\n", parser->token->content);
	cteate(parser);
	return(parser->code);
}

int writing_in_file(t_pars *parser)
{
	int fd;
	char *bytecode;
	int i;
	int len;

//	len = 4 + 4 + PROG_NAME_LENGTH + 4 + 4 + 4 + COMMENT_LENGTH + 4 + parser->code_size;
	len = 8;
	i = 0;
	if ((fd = open("filename.cor", O_CREAT | O_WRONLY, 0644)) == -1)
		return(-1);
	if (!(bytecode = ft_strnew((size_t)parser->code_size)))
		return(-1);
	int_to_byte(bytecode, i, COREWAR_EXEC_MAGIC, 4);/*
	i += 4;
	ft_memcpy(&bytecode[i], parser->name, ft_strlen(parser->name));
	i += PROG_NAME_LENGTH;
	i += 4;
	int_to_byte(bytecode, i, parser->code_size, 4);
	i += 4;
	ft_memcpy(&bytecode[i], parser->comment, ft_strlen(parser->comment));
	i += COMMENT_LENGTH;
	i += 4;
	ft_memcpy(&bytecode[i], parser->code, parser->code_size);*/
	i+= 4;
	neg_to_byte(bytecode, i, -19, 4);
	write(fd, bytecode, len);
	return(1);

}
int main()
{
	char *code;
	t_pars *parser;

	parser = parser_init();
//	code = assembler(parser);
	writing_in_file(parser);
	return(1);
}
