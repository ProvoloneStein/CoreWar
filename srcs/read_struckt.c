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


int what_function(t_pars *parser, char **bytecode)
{
    if (!ft_strcmp1(parser->token->content, "live"))
        return (ft_live(parser, bytecode));
    else if (!ft_strcmp(parser->token->content, "ldi"))
        return (ft_ldi(parser, bytecode));
    else if (!ft_strcmp(parser->token->content, "ld"))
        return (ft_ld(parser, bytecode));
    else if (!ft_strcmp(parser->token->content, "sti"))
        return (ft_sti(parser, bytecode));
    else if (!ft_strcmp(parser->token->content, "add"))
        return (ft_add(parser, bytecode));
    else if (!ft_strcmp(parser->token->content, "sub"))
        return (ft_sub(parser, bytecode));
    else if (!ft_strcmp(parser->token->content, "and"))
        return (ft_and(parser, bytecode));
    else if (!ft_strcmp(parser->token->content, "or"))
        return (ft_or(parser, bytecode));
    else if (!ft_strcmp(parser->token->content, "xor"))
        return (ft_xor(parser, bytecode));
    else if (!ft_strcmp(parser->token->content, "zjmp"))
        return (ft_zjmp(parser, bytecode));
    else if (!ft_strcmp(parser->token->content, "sti"))
        return (ft_sti(parser, bytecode));
    else if (!ft_strcmp(parser->token->content, "fork"))
        return (ft_fork(parser, bytecode));
    else if (!ft_strcmp(parser->token->content, "lldi"))
        return (ft_lldi(parser, bytecode));
    else if (!ft_strcmp(parser->token->content, "lld"))
        return (ft_lld(parser, bytecode));
    else if (!ft_strcmp(parser->token->content, "lfork"))
        return (ft_lfork(parser, bytecode));
    else if (!ft_strcmp(parser->token->content, "aff"))
        return (ft_aff(parser, bytecode));
    return (0);
}

int make_code(t_pars *parser, char **bytecode)
{
    t_token *head;

    head = parser->token;
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
            if (what_function(parser, bytecode))
                //continue;
                ft_printf("KEK");
            else
                return(-1);
        }
        else
            return(-1);    
    }
    return(1);
}