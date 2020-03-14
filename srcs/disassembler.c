#include "disassem.h"

int32_t		bytecode_to_int32(const uint8_t *bytecode, size_t size)
{
	int32_t	result;
	_Bool	sign;
	int		i;

	result = 0;
	sign = (_Bool)(bytecode[0] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((bytecode[size - 1] ^ 0xFF) << (i++ * 8));
		else
			result += bytecode[size - 1] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

static char *create_file_s(char *filename)
{
	int i;
	char	*out_name;

	out_name = (char*)ft_memalloc(sizeof(char) * (ft_strlen(filename) + 3));
	ft_strcpy(out_name, filename);
	i = 0;
	while (out_name[i] != '\0')
		i++;
	out_name[i - 1] = 'c';
	out_name[i] = 'o';
	out_name[i + 1] = 'r';
	out_name[i + 2] = '\0';
	return(out_name);
}

t_read *reader_init(char *progname)
{
	t_read *pars;

	pars = (t_read*)malloc(sizeof(t_read));
	pars->comment = NULL;
	pars->name = NULL;
	pars->i = 0;
	pars->arg_types = 0;
	pars->code_size = 0;
    pars->code = NULL;
	pars->filename = create_file_s(progname);
	return(pars);
}

void free_read(t_read *reader)
{
	if (reader->name)
		free(reader->name);
	if (reader->comment)
		free(reader->comment);
	if (reader->code)
		free(reader->code);
	if (reader->filename)
		free(reader->filename);
	free(reader);		
}


void hero_code(t_read *reader, char **code)
{


	while(reader->i < reader->code_size)
	{
		if (reader->code[reader->i]  >= 0x01 && reader->code[reader->i] <= 0x10)
			*code = ft_strplus(*code, hero_func(reader), 1, 1);
		else
			exit(0);
	}
}


int disassembler(char *filename)
{
    t_read *reader;
    char *code;
    int fd;

	code = ft_strnew(0);
    if ((fd = open(filename, O_RDONLY)) == -1)
		exit(1);
    reader = reader_init(filename);
    read_codefile(reader, fd);
	close(fd);
	hero_code(reader, &code);
	if ((fd = open(reader->filename, O_CREAT| O_TRUNC | O_WRONLY, 0644)) == -1)
		return (-1);
	write(fd, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING));
	write(fd, " \"", 2);
	write(fd, reader->name, ft_strlen(reader->name));
	write(fd, "\"\n", 2);
	write(fd, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING));
	write(fd, " \"", 2);
	write(fd, reader->comment, ft_strlen(reader->comment));
	write(fd, "\"\n", 2);
	write(fd, code, ft_strlen(code));
	write(fd, "\n", 1);
	close(fd);
	free_read(reader);
	free(code);	
	return(1);
}