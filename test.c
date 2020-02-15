#include "assem.h"
#include "op.h"

t_pars *parser_init()
{
	t_pars *pars;

	pars = (t_pars*)malloc(sizeof(t_pars));
	pars->comment = NULL;
	pars->name = NULL;
	pars->row = 0;
	pars->column = 0;
	return(pars);
}



t_token *token_init(t_pars *parser, t_type type)
{
	t_token *token;

	token = (t_token*)malloc(sizeof(t_token));
	token->column = parser->column;
	token->row = parser->row;
	token->type = type;
	token->next = NULL;
	token->content = NULL;
	return(token);
}

void add_token(t_pars *parser, t_token *token)
{
	t_token *head;

	head = parser->token;
	if (parser->token)
	{
		head = parser->token;
		while(parser->token->next)
		{
			parser->token = parser->token->next;
		}
		parser->token->next = token;
		parser->token = head;
	}
	else
		parser->token = token;
}

void take_token(t_pars *parser, char **line)
{
	if (line[parser->column] == '.')
		token_content();
	else if (line[parser->column] == SEPARATOR_CHAR)
		add_token(parser, token_init(parser, SEPARATOR_CHAR));
	else if (line[parser->column] == '\n')
		add_token(parser, token_init(parser, NEW_LINE));
	else if (line[parser->column] == DIRECT_CHAR)
	else if (line[parser->column] == '\"')
	else if (line[parser->column] == LABEL_CHAR)
	else
}

void reader(int fd, t_pars *parser)
{
	char *line;
	int err;

	while(++(parser->row) && (err = get_next_line(fd, &line)) > 0)
	{
		parser->column = 0;
		while(line[parser->column])
		{
			ft_clear_line(parser, line);
			if (line[parser->column])
				take_token(parser, &line);
		}
		ft_strdel(&line);
	}
	if (err == -1)
	{
		ft_printf("NE CHITAL\n");
		exit();
	}
	token_init(END);
}

void assembler(int fd)
{
	t_pars *parser;

	parser = parser_init();
	read_tok(fd, parser);
	ft_printf("%s %s 123", parser->name, parser->comment);
}

int main()
{
	int fd;
	char *bytecode;
	int32_t len = 4;

	if ((fd = open("filename.s", O_RDONLY)) == -1)
		return(-1);
	assembler(fd);	
	if ((fd = open("filename.cor", O_CREAT | O_WRONLY, 0644)) == -1)
		return(-1);
	if (!(bytecode = ft_strnew((size_t)len)))
		return(1);
	int32_to_byte(bytecode, 0, COREWAR_EXEC_MAGIC, 4);
	write(fd, bytecode, (size_t)len);	
	return(1);
}
