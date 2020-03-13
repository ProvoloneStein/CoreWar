#include "disassem.h"


int32_t		bytecode_to_int32(const uint8_t *bytecode, size_t size)
{
	int32_t	result;
	t_bool	sign;
	int		i;

	result = 0;
	sign = (t_bool)(bytecode[0] & 0x80);
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



char *ft_progname(char *name)
{
    char *str;
    int i;
    int j;

     j = 0;
     i = ft_strlen(name);
     str = (char*)malloc(sizeof(char) * (i - 2));
     while(j != i - 2)
     {
         str[j] = name[j];
		 j++;
     }
	 str[j] = '\0';
     str = ft_strplus(str, ".cor", 1, 0);
     return(str);
}

t_reader *reader_init(char *progname)
{
	t_reader *pars;

	pars = (t_reader*)malloc(sizeof(t_reader));
	pars->comment = NULL;
	pars->name = NULL;
	pars->line = 0;
	pars->i = 0;
	pars->column = 0;
	pars->code_size = 0;
    pars->code = NULL;
	pars->f_head = 0;
	pars->filename = ft_progname(progname);
	ft_printf("%s\n", pars->filename);
	return(pars);
}



void hero_code(t_read reader, char **code)
{
	size_t i;

	while(reader->code[i] < reader->code_size)
	{
		if (reader->code[i] >= 0x00 && readeer->code <= 0x10)
		{
			hero_func(reader, code);
		}
		else
			erro;
}


int disassembler(char *str)
{
    t_read *reader;
    char *code;
    int fd;
    int i;
    int num;

	code = ft_strnew(0);
    if ((fd = open(filename, O_RDONLY)) == -1)
		terminate(ERR_OPEN_FILE);
    reader = reader_init(str);
    read_codefile(reader, fd);
	hero_code(reader, &code);


}