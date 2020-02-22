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
    if (ft_strequ(parser->token->content, "live"))
        return(ft_live(parser));
    return(NULL);    
}

int cteate(t_pars *parser)
{
    char *bytecode;
    t_token *head;

    head = parser->token;
    bytecode = NULL;
    parser->byte = 136;
    while (parser->token->type == 1)
        if (make_com(parser) != 1)
            return(-1);
//    if (!(parser->comment && parser->name))
//        return(-1);
    while (parser->token && parser->token->type != END)
    {
        if (parser->token->type == NEW_LINE && parser->token->type == LABEL)//1
            parser->token = parser->token->next;
        else if (parser->token->type == LABEL)//1
            what_function(parser);
       /* else if(parser->token->type == MENTION)
            make_mention();*/
        else
            return(-1);    
    }
    return(1);
}