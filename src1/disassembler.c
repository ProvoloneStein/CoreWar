#include "disassem.h"

char *ft_progname1(char *name)
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
     str = ft_strplus(str, ft_strdup(".s"), 1, 1);
     return(str);
}


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
	pars->filename = ft_progname1(progname);
	ft_printf("%s\n", pars->filename);
	return(pars);
}



void hero_code(t_read *reader, char **code)
{


	while(reader->i < reader->code_size)
	{
		if (reader->code[reader->i]  >= 0x00 && reader->code[reader->i] <= 0x10)
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
    int i;
    int num;

	code = ft_strnew(0);
    if ((fd = open(filename, O_RDONLY)) == -1)
		exit(1);
    reader = reader_init(filename);
    read_codefile(reader, fd);
	clode(fd);
	hero_code(reader, &code);
	if ((fd = open(reader->filename, O_CREAT | O_WRONLY, 0644)) == -1)
		return (-1);
	ft_printf("Writing in file %s\n", pars->filename);
	write(fd, code, ft_strlen(code));
	close(fd);
	free(code);	
	return(1);
}