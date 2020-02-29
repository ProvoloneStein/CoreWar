#include "assem.h"

int ft_aff(t_pars *parser, char **bytecode)
{
    parser->token = parser->token->next;
    int_to_byte(*bytecode, parser->i, 0x10, NAME_SIZE);
    parser->i += NAME_SIZE;
    if (!(arg_type(parser, 1, bytecode)))
        return(0);
    if ((next_arg(parser, 3, 2, bytecode)))
    {
     //   parser->token = parser->token->next;
        return(1);
    }
    return(0);
}