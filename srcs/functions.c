#include "assem.h"

/*
** я создаю отдельно каждую переменную. Мне нужно знать ее тип в виде токена. и контент собсна
*/
/*
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
}*/

void	int_to_byte(char *data,int32_t pos, int32_t value, size_t size)
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

int arg_type(t_pars *parser, int size, char **code)
{
    int num;
    t_token *head;
    int i;

    head = parser->token;
    num = 0;
    i = 0;
    while (size > 0)
    {
        if (parser->token->next->type == DIRECT || parser->token->next->type == DIRECT_LABEL)
        {
            num = num | (1 << i);
            i += 2;
        }
        else if (parser->token->next->type == INDIRECT || parser->token->next->type == INDIRECT_LABEL)
        {
            num = num | (1 << i);
            num = num | (1 << (i + 1));
            i += 2;
        }
        else if (parser->token->next->type == REGISTER)
        {
            num = num | (1 << (i + 1));
            i += 2;
        }
        else
        {
            parser->token = head;
            return(0);
        }
        size--;
    }
    parser->token = head;
    int_to_byte(*code, parser->i, i, 1);
    parser->i += 1;
    return (1);
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

int next_arg(t_pars *parser, int type, int size, char **bytecode)
{

    if ((parser->token->next->type == DIRECT || parser->token->next->type == DIRECT_LABEL) && (write_dir(parser, size, bytecode) != -1)
                    && (type == 1 || type == 4 || type == 5 || type == 7))
    {
        parser->token = parser->token->next;
        return(1);
    }
    else if ((parser->token->next->type == INDIRECT || parser->token->next->type == INDIRECT_LABEL) && (write_indir(parser, bytecode) != -1)
        && (type == 2 || type == 4 || type == 6 || type == 7))
    {
        parser->token = parser->token->next;
        return(1);
    }
    else if ((parser->token->next->type == REGISTER) && (write_reg(parser, bytecode) != -1)
        && (type == 3 || type == 5 || type == 6 || type == 7))
    {    
        parser->token = parser->token->next;
        return(1);
    }
    return (-1);

}
int find_value(t_pars *parser)
{
    t_ment *head;
    int i;

    head = parser->mention;
    i = 0;
    while (parser->mention && !(ft_strcmp(parser->mention->name, parser->token->next->content)))
        parser->mention = parser->mention->next;
    if (parser->mention)
            i = parser->token->next->byte - parser->mention->byte;
    return (i);
}

int write_dir(t_pars *parser, size_t size, char **bytecode)
{
    int num;

    if (!(parser->token->next->content))
        return(-1);
    if (parser->token->next->type == DIRECT_LABEL)
    {
        num = find_value(parser);
        int_to_byte(*bytecode, parser->i, num, size);
    }
    else if (parser->token->next->type == DIRECT)
    {
        int_to_byte(*bytecode, parser->i, ft_atoi(parser->token->next->content), size);
    }
    else
        return(-1);
    parser->i += size;
    return (1);
}

int write_indir(t_pars *parser, char **bytecode)
{
    int num;

    if (!(parser->token->next->content))
        return(-1);
    if (parser->token->next->type == INDIRECT_LABEL)
    {
        num = find_value(parser);
        int_to_byte(*bytecode, parser->i, num, IND_SIZE);
    }
    else if (parser->token->next->type == INDIRECT)
    {
        int_to_byte(*bytecode, parser->i, ft_atoi(parser->token->content), IND_SIZE);
    }
    else
        return(-1);
    parser->i += IND_SIZE;
    return (1);
}

int write_reg(t_pars *parser, char **bytecode)
{
    if (!(parser->token->next->content))
        return(-1);
    if (parser->token->next->type == INDIRECT)
    {
        int_to_byte(*bytecode, parser->i, ft_atoi(parser->token->content), REG_SIZE);
    }
    else
        return(-1);
    parser->i += REG_SIZE;
    return (1);
}
