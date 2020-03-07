#include "disassem.h"

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
	pars->i = 0;//это для печати
	pars->column = 0;
	pars->code_size = 0;
	pars->f_head = 0;
	pars->filename = ft_progname(progname);
	ft_printf("%s\n", pars->filename);
	return(pars);
}

char *rd_chr(char *str, int *i, int size)
{
    char *line;

    line = ft_strnew(1);
    while(str[*i] || size > 0)
    {
        ft_strplus_c(line, str[*i], 1);
        (*i)++;
    }
    return(line);
}

int hex_to_int(char *str, int *i, int size)
{
    char *line;

    line = rd_chr(str, i, size);
    ft_atoi
}

int disassembler(char *str)
{
    t_reader *reader;
    char *code;
    int fd;
    int i;
    int num;

    fd = open(str, O_RDONLY);
    reader = reader_init(str);
    if (get_next_line(fd, &code) < 1)
        return (0);
    i = 3;
    num = ft_strlen(str);
    if (i + PROG_NAME_LENGTH > num)
        return(0);
    reader->name = rd_chr(str, &i, 4);
    i += 4;

}