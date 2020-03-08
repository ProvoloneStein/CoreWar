
int     g_line = 1;
int     g_column = 1;
int     g_end = 0;
int     g_byte = 0;
char*   g_link_chars = "abcdefghijklmnopqrstuvwxyz_0123456789";

#include "assem.h"

int     read_map(char** map, char* fd_map)
{
    char    buf[BUFF_SIZE + 1];
    char*   temp1;
    int     i;
    int     fd;

    *map = 0;
    fd = open(fd_map, O_RDONLY);
    while ((i = read(fd, buf, BUFF_SIZE)))
    {
        buf[i] = '\0';
        temp1 = ft_strjoin(*map, buf);
        if (*map)
            free(*map);
        *map = temp1;
    }
    return check_map(*map);
}

t_oken  find_token(char* c, t_token** tok, t_pars* pars)
{
    int     flag;

    flag = 0;
    skip_space(c);
    (*tok)->column = g_column;
    (*tok)->line = g_line;
    if (get_tok(c, tok) != -1)
        return get_tok(c, tok);
    while (ft_strchr(g_link_chars, c[g_end]) && c[g_end])
    {
        flag = 1;
        score_line(c, 1, 1);
    }
    pars->code_size = pars->token->byte;
    if (!c[g_end])
        return END;
    else if (c[g_end] == ':' && flag)
        return LABEL;
    err_handler(1, (*tok)->column, (*tok)->line);
    return 0;
}

t_token *create_elem()
{
    t_token  *tokenElem;

    tokenElem = (t_token*)malloc(sizeof(t_token));
    tokenElem->type = END;
    tokenElem->byte = g_byte;
    tokenElem->column = g_column;
    tokenElem->content = 0;
    tokenElem->line = g_line;
    tokenElem->next = 0;
    return tokenElem;
}

void get_next_metion(t_pars* pars, char* map, t_ment** temp1)
{
    t_ment  *ment;
    int len;

    len = 0;
    skip_sp(map);
    while (map[g_end + len] != ':')
        len++;
    ment = (t_ment*)malloc(sizeof(t_ment));
    ment->name = ft_strsub(map, g_end, len);
    ment->byte = g_byte;
    ment->next = 0;
    if (!pars->mention)
    {
        pars->mention = ment;
        *temp1 = ment;
    }
    else
    {
        pars->mention->next = ment;
        pars->mention = pars->mention->next;
    }
    score_line(map, len + 1, 1);
}

int    create_list(char* fd_map, t_pars* pars)
{
    t_token *temp;
    t_ment *temp1;
    char* map;

    temp1 = 0;
    pars->token = create_elem();
    temp = pars->token;
    if (!read_map(&map, fd_map))
        err_handler(0, 1, 1);
    while (map[g_end])
    {
        pars->token->type = find_token(map, &pars->token, pars);
        if (pars->token->type == LABEL)
            take_label(pars, map, &temp1);
        if (pars->token->type != END && pars->token->type != LABEL)
            take_ins(pars, map);
        if (pars->token->type == END)
            pars->code_size = pars->token->byte;
    }
    pars->token = temp;
    pars->mention = temp1;
    return (1);
}
