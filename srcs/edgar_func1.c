#include "assem.h"

int     g_line;
int     g_column;
int     g_end;
int     g_byte;
char*   g_link_chars;

t_oken  get_tok(char* c)
{
    if (if_name(c + g_end))
        return NAME;
    else if (if_comment(c + g_end))
        return COMMENT;
    else if (if_operation(c + g_end))
        return INSTRUCTION;
    return (ERROR);
}

void    skip_sp(char* map)
{
    while (map[g_end] != '\n')
        score_line(map, 1, 0);
    score_line(map, 1, 1);
    while (map[g_end] == ' ' || map[g_end] == '\t')
        score_line(map, 1, 1);
}

void    take_label(t_pars* pars, char* map, t_ment** temp1)
{
    get_next_metion(pars, map, temp1);
    pars->token->next = create_elem();
    pars->token = pars->token->next;
    check_unique_label(*temp1);
}

void    take_ins(t_pars* pars, char* map)
{
    pars->token->content = get_content(map, pars->token->type);
    if (pars->token->type == INSTRUCTION)
        add_variables(&pars->token, map);
    pars->token->next = create_elem();
    pars->token = pars->token->next;
}