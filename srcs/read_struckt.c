#include "assem.h"
#include "op.h"

int make_com(t_pars *parser)
{
    if (parser->token && ft_strcmp(parser->token->content, "name") && parser->name == NULL)
    {
        if (parser->token->next && ft_strlen(parser->token->next->content) <= PROG_NAME_LENGTH) //???
        {
            parser->name = parser->token->next->content;
            parser->token = parser->token->next->next;
        }
        else
            return(-1);
    }
    else if (parser->token && ft_strcmp(parser->token->content, "comment") && parser->comment == NULL)
    {
        if (parser->token->next && ft_strlen(parser->token->next->content) <= COMMENT_LENGTH) //?
        {
            parser->comment = parser->token->next->content;
            parser->token = parser->token->next->next;
        }
        else
            return(-1);
    }
    else
        return(-1);
    return(1);    
}


char *what_function(t_pars *parser)
{
    if (!ft_strcmp1(parser->token->content, "live"))
        return (ft_live(parser));
    else if (!ft_strcmp(parser->token->content, "ldi"))
        return (ft_ldi(parser));
    else if (!ft_strcmp(parser->token->content, "ld"))
        return (ft_ld(parser));
    else if (!ft_strcmp(parser->token->content, "sti"))
        return (ft_sti(parser));
    else if (!ft_strcmp(parser->token->content, "add"))
        return (ft_add(parser));
    else if (!ft_strcmp(parser->token->content, "sub"))
        return (ft_sub(parser));
    else if (!ft_strcmp(parser->token->content, "and"))
        return (ft_and(parser));
    else if (!ft_strcmp(parser->token->content, "or"))
        return (ft_or(parser));
    else if (!ft_strcmp(parser->token->content, "xor"))
        return (ft_xor(parser));
    else if (!ft_strcmp(parser->token->content, "zjmp"))
        return (ft_zjmp(parser));
    else if (!ft_strcmp(parser->token->content, "sti"))
        return (ft_sti(parser));
    else if (!ft_strcmp(parser->token->content, "fork"))
        return (ft_fork(parser));
    else if (!ft_strcmp(parser->token->content, "lldi"))
        return (ft_lldi(parser));
    else if (!ft_strcmp(parser->token->content, "lld"))
        return (ft_lld(parser));
    else if (!ft_strcmp(parser->token->content, "lfork"))
        return (ft_lfork(parser));
    else if (!ft_strcmp(parser->token->content, "aff"))
        return (ft_aff(parser));
    return (NULL);
}

int make_code(t_pars *parser)
{
    char *bytecode;
    t_token *head;

    head = parser->token;
    bytecode = NULL;
    while (parser->token->type == 1)
        if (make_com(parser) != 1)
            return(-1);
//    if (!(parser->comment && parser->name))
//        return(-1);
    while (parser->token && parser->token->type != END)
    {
//        if (parser->token->type == LABEL)//1 parser->token->type == NEW_LINE && 
//            parser->token = parser->token->next;
       if (parser->token->type == INSTRUCTION)//1
        {
            if ((bytecode = what_function(parser)))
                parser->code = ft_strplus(parser->code, bytecode, 1, 1);
            else
                return(-1);
        }
        else
            return(-1);    
    }
    return(1);
}