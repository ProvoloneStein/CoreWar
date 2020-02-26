#include "assem.h"

char *ft_aff(t_pars *parser)
{
    char *codeline;
    char *param;

    codeline = ft_strnew(NAME_SIZE + 1);
    int_to_byte(codeline, 0, 0x10, NAME_SIZE);
    if (!(arg_type(parser, 1, codeline)))
    {
        free(codeline);
        return(NULL);
    }
    if ((param = next_arg(parser, 3, 2)))
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        parser->token = parser->token->next;
        return(codeline);
    }
    free(codeline);
    return(NULL);
}