#include "assem.h"

char *ft_sti(t_pars *parser)
{
    char *codeline;
    char *param;
    int size;

    size = 0;
    codeline = ft_strnew(NAME_SIZE + 1);
    int_to_byte(codeline, 0, 0x0b, NAME_SIZE);
    if (!(arg_type(parser, 3, codeline)))
    {
        free(codeline);
        return(NULL);
    }
    if ((param = next_arg(parser, 3, 2)))
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        size++;
    }
    if ((param = next_arg(parser, 7, 2)) && size == 1)
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        size++;
    }
    if ((param = next_arg(parser, 5, 2)) && size == 2)
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        parser->token = parser->token->next;
        return(codeline);
    }
    free(codeline);
    return(NULL);
}

char *ft_fork(t_pars *parser)
{
    char *codeline;
    char *param;

    codeline = ft_strnew(NAME_SIZE + 1);
    int_to_byte(codeline, 0, 0x0c, NAME_SIZE);
    if ((param = next_arg(parser, 1, 2)))
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        parser->token = parser->token->next;
        return(codeline);
    }
    free(codeline);
    return(NULL);
}

char *ft_lld(t_pars *parser)
{
    char *codeline;
    char *param;
    int size;

    size = 0;
    codeline = ft_strnew(NAME_SIZE + 1);
    int_to_byte(codeline, 0, 0x0d, NAME_SIZE);
    if (!(arg_type(parser, 2, codeline)))
    {
        free(codeline);
        return(NULL);
    }
    if ((param = next_arg(parser, 4, 4)))
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        size++;
    }
    if ((param = next_arg(parser, 3, 4)) && size == 1)
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        parser->token = parser->token->next;
        return(codeline);
    }
    free(codeline);
    return(NULL);
}

char *ft_lldi(t_pars *parser)
{
    char *codeline;
    char *param;
    int size;

    size = 0;
    codeline = ft_strnew(NAME_SIZE + 1);
    int_to_byte(codeline, 0, 0x0e, NAME_SIZE);
    if (!(arg_type(parser, 3, codeline)))
    {
        free(codeline);
        return(NULL);
    }
    if ((param = next_arg(parser, 7, 2)))
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        size++;
    }
    if ((param = next_arg(parser, 5, 2)) && size == 1)
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        size++;
    }
    if ((param = next_arg(parser, 3, 2)) && size == 2)
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        parser->token = parser->token->next;
        return(codeline);
    }
    free(codeline);
    return(NULL);
}

char *ft_lfork(t_pars *parser)
{
    char *codeline;
    char *param;

    codeline = ft_strnew(NAME_SIZE + 1);
    int_to_byte(codeline, 0, 0x0f, NAME_SIZE);
    if ((param = next_arg(parser, 1, 2)))
    {
        codeline = ft_strplus(codeline, param, 1, 1);
        parser->token = parser->token->next;
        return(codeline);
    }
    free(codeline);
    return(NULL);
}