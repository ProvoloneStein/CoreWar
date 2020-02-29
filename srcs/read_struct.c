#include "assem.h"
#include "op.h"

int make_com(t_pars *parser)
{
    if (parser->token->type == COMMENT && parser->comment == NULL)
    {
        if (ft_strlen(parser->token->content) <= COMMENT_LENGTH) //?
        {
            parser->comment = parser->token->content;
            parser->token = parser->token->next;
        }
        else
            return(0);
    }
    else
        return(0);
    return(1);    
}

int make_name(t_pars *parser)
{
    if (parser->token->type == NAME && parser->name == NULL)
    {
        if (ft_strlen(parser->token->content) <= PROG_NAME_LENGTH) //??
        {
            parser->name = parser->token->content;
            parser->token = parser->token->next;
        }
        else
            return(0);
    }
    else
        return(0);
    return(1);    
}

int check_commands(t_pars *parser)
{
    t_token *head;

    head = parser->token;
    while (parser->token && (parser->token->type == NAME || parser->token->type == COMMENT))
    {
        if (make_name(parser) || make_com(parser))
            continue;
        parser->token = head;
        return (-1);
    }
    parser->token = head;
    return (1);
}


int what_function(t_pars *parser, char **bytecode)
{
    if (!ft_strcmp1(parser->token->content, "live"))
        return (ft_live(parser, bytecode));
    else if (!ft_strcmp1(parser->token->content, "ldi"))
        return (ft_ldi(parser, bytecode));
    else if (!ft_strcmp1(parser->token->content, "ld"))
        return (ft_ld(parser, bytecode));
    else if (!ft_strcmp1(parser->token->content, "sti"))
        return (ft_sti(parser, bytecode));
    else if (!ft_strcmp1(parser->token->content, "add"))
        return (ft_add(parser, bytecode));
    else if (!ft_strcmp1(parser->token->content, "sub"))
        return (ft_sub(parser, bytecode));
    else if (!ft_strcmp1(parser->token->content, "and"))
        return (ft_and(parser, bytecode));
    else if (!ft_strcmp1(parser->token->content, "or"))
        return (ft_or(parser, bytecode));
    else if (!ft_strcmp1(parser->token->content, "xor"))
        return (ft_xor(parser, bytecode));
    else if (!ft_strcmp1(parser->token->content, "zjmp"))
        return (ft_zjmp(parser, bytecode));
    else if (!ft_strcmp1(parser->token->content, "sti"))
        return (ft_sti(parser, bytecode));
    else if (!ft_strcmp1(parser->token->content, "fork"))
        return (ft_fork(parser, bytecode));
    else if (!ft_strcmp1(parser->token->content, "lldi"))
        return (ft_lldi(parser, bytecode));
    else if (!ft_strcmp1(parser->token->content, "lld"))
        return (ft_lld(parser, bytecode));
    else if (!ft_strcmp1(parser->token->content, "lfork"))
        return (ft_lfork(parser, bytecode));
    else if (!ft_strcmp1(parser->token->content, "aff"))
        return (ft_aff(parser, bytecode));
    return (0);
}

int make_code(t_pars *parser, char **bytecode)
{
    t_token *head;

    head = parser->token;
    while (parser->token->type == NAME || parser->token->type == COMMENT)
        parser->token = parser->token->next;
//    if (!(parser->comment && parser->name))
//        return(-1);
    while (parser->token && parser->token->type != END)
    {
//        if (parser->token->type == LABEL)//1 parser->token->type == NEW_LINE && 
//            parser->token = parser->token->next;
       if (parser->token->type == INSTRUCTION)//1
        {
            if (what_function(parser, bytecode))
                ft_printf("\nfun\n");
            else
                return(-1);
        }
        else if (parser->token->type == LABEL)
            parser->token = parser->token->next;
        else
            return(-1);    
    }
    return(1);
}