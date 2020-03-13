void print_dir(uint8_t *bytecode, char **code, int size)
{
    char *arg;

    arg = ft_strplus("%%", ft_itoa(bytecode_to_int32()));
}

void print_indir(char *bytecode, char **code)
{
    char *arg;

    arg = ft_strplus("%%", ft_itoa(bytecode_to_int32()));
    ft_strplus(*code, arg, 1, 1);
}

void print_reg(char *bytecode, char **code)
{
    char *arg;

    arg = ft_strplus("r", ft_itoa(bytecode_to_int32()));
    ft_strplus(*code, arg, 1, 1);
}

/*
** arg types
** DIR = 1
** INDIR = 2
** REG = 3
** DIR || INDIR = 4
** DIR || REG = 5
** INDIR || REG = 6
** DIR || INDIR || REG = 7
*/


int print_arg(uint8_t byte, char **code, int size, int type, int num)
{
    int bit;

    bit = 8 - 2 * num;

    if ((byte) & (uint8_t)3)
        exit();
    if ((type == 1 || type == 4 || type == 5 || type == 7) && ((byte >> bit) & (uint8_t)3) == (uint8_t)2)
        print_dir;
    else if(((type == 2 || type == 4 || type == 6 || type == 7) && ((byte >> bit) & (uint8_t)3) == (uint8_t)3)
        print_indir;
     else if(((type == 3 || type == 5 || type == 6 || type == 7) && ((byte >> bit) & (uint8_t)3) == (uint8_t)1)    

}

int ft_d_live(t_read *reader, char **code, int *i)
{
    ft_strplus(*code, "live ", 1, 0);
    (*i)++;
    print_dir(reader->code + *i, code, 4);
    *i += 4;
}

int ft_d_xor(t_read *reader, char **code, int *i)
{
    ft_strplus(*code, "xor ", 1, 0);
    (*i)++;
    print_arg(reader->code + *i, code, 4, 7);
    *i += 4;
}