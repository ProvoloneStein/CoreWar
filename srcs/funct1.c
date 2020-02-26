#include "assem.h"
char *ft_live(t_pars *parser)
{
    char *codeline;
    char *param;

    codeline = ft_strnew(NAME_SIZE + 1);
    int_to_byte(codeline, 0, 0x01, NAME_SIZE);
    if (param = next_arg(parser, 1, 4))
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        parser->token = parser->token->next;
        return(codeline);
    }
    free(codeline);
    return(NULL);
}

char *ft_ld(t_pars *parser)
{
    char *codeline;
    char *param;
    int size;

    size = 0;
    codeline = ft_strnew(NAME_SIZE + 1);;
    int_to_byte(codeline, 0, 0x02, NAME_SIZE);
    if (!(arg_type(parser, 2, codeline)))
    {
        free(codeline);
        return(NULL);
    }
    if (param = next_arg(parser, 1, 4))
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        size++;
    }
    if ((param = next_arg(parser, 4, 4)) && size == 1)
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        parser->token = parser->token->next;
        return(codeline);
    }
    free(codeline);
    return(NULL);
}

char *ft_st(t_pars *parser)
{
    char *codeline;
    char *param;
    int size;

    size = 0;
    codeline = ft_strnew(NAME_SIZE + 1);
    int_to_byte(codeline, 0, 0x03, NAME_SIZE);
    if (!(arg_type(parser, 2, codeline)))
    {
        free(codeline);
        return(NULL);
    }
    if (param = next_arg(parser, 3, 4))
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        size++;
    }
    if ((param = next_arg(parser, 6, 4)) && size == 1)
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        parser->token = parser->token->next;
        return(codeline);
    }
    free(codeline);
    return(NULL);
}
char *ft_add(t_pars *parser)
{
    char *codeline;
    char *param;
    int size;

    size = 0;
    codeline = ft_strnew(NAME_SIZE + 1);
    int_to_byte(codeline, 0, 0x04, NAME_SIZE);
    if (!(arg_type(parser, 3, codeline)))
    {
        free(codeline);
        return(NULL);
    }
    if (param = next_arg(parser, 3, 4))
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        size++;
    }
    if ((param = next_arg(parser, 3, 4)) && size == 1)
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        size++;
    }
    if ((param = next_arg(parser, 3, 4)) && size == 2)
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        parser->token = parser->token->next;
        return(codeline);
    }
    free(codeline);
    return(NULL);
}

char *ft_sub(t_pars *parser)
{
    char *codeline;
    char *param;
    int size;

    size = 0;
    codeline = ft_strnew(NAME_SIZE + 1);
    int_to_byte(codeline, 0, 0x05, NAME_SIZE);
    if (!(arg_type(parser, 3, codeline)))
    {
        free(codeline);
        return(NULL);
    }
    if (param = next_arg(parser, 3, 4))
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        size++;
    }
    if ((param = next_arg(parser, 3, 4)) && size == 1)
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        size++;
    }
    if ((param = next_arg(parser, 3, 4)) && size == 2)
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        parser->token = parser->token->next;
        return(codeline);
    }
    free(codeline);
    return(NULL);
}