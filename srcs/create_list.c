//
// Created by Greyjoy Aliza on 2020-02-23.
//

int     g_line = 1;
int     g_column = 1;
int     g_end;
int     g_byte;
char*   g_link_chars = "abcdefghijklmnopqrstuvwxyz_0123456789";

#include "assem.h"

void    score_line(char* c, int value, int ascending)
{
    while (value)
    {
        if (ascending)
        {
            if (c[g_end] == '\n')
            {
                g_column = 1;
                g_line++;
            }
            else
                g_column++;
            g_end++;
        }
        else
        {
            if (c[g_end - 1] == '\n')
            {
                g_column = 0;
                while (c[g_end + g_column] != '\n')
                    g_column++;
                g_column++;
                g_line--;
            }
            else
                g_column--;
            g_end--;
        }
        value--;
    }
}

char *get_content(char *map, t_oken token)
{
    char*   temp;
    int     i;
    int     start;
    int     len;

    i = 0;
    start = 0;
    len = 0;
    if (token == NAME || token == COMMENT)
        while (*map && i != 2)
        {
            if (map[start + g_end] == '"' && i == 0)
                i = 1;
            else if (i == 0)
                start++;
            if (i == 1)
                len++;
            if (map[start + len + g_end] == '"' && i == 1)
                i = 2;
        }
    else if (token == INSTRUCTION)
    {
        temp = find_operation(map + g_end);
        return ft_strdup(temp);
    }
    temp = ft_strsub(map, start + g_end + 1, len - 1);
    score_line(map, start + len + 1, 1);
    return temp;
}

void    read_map(char** map, char* fd_map)
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
}

t_oken  find_token(char* c, t_token** tok)
{
    int     flag;

    flag = 0;
    while ((c[g_end] == ' ' || c[g_end] == '\t' || c[g_end] == '\n' || c[g_end] == '#' || c[g_end] == ',') && c[g_end])
    {
        if (c[g_end] == '#')
            while (c[g_end] != '\n' && c[g_end])
                score_line(c, 1, 1);
        else
            score_line(c, 1, 1);
    }
    (*tok)->column = g_column;
    (*tok)->line = g_line;
    if (!ft_strcmp1(c + g_end, ".name"))
        return NAME;
    else if (!ft_strcmp1(c + g_end, ".comment"))
        return COMMENT;
    else if (find_operation(c + g_end))
    {
        g_byte++;
        (*tok)->byte = g_byte;
        return INSTRUCTION;
    }
    while (ft_strchr(g_link_chars, c[g_end]) && c[g_end])
    {
        flag = 1;
        score_line(c, 1, 1);
    }
    if (!c[g_end])
        return END;
    else if (c[g_end] == ':' && flag)
        return LABEL;
    return ERROR;
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
    while (map[g_end] != '\n')
        score_line(map, 1, 0);
    score_line(map, 1, 1);
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

t_token *create_list(char* fd_map, t_pars* pars)
{
    t_token *temp;
    t_ment *temp1;
    char* map;

    pars->token = create_elem();
    temp = pars->token;
    temp1 = 0;
    read_map(&map, fd_map);
    g_end = 0;
    g_byte = 0;
    while (map[g_end])
    {
        pars->token->type = find_token(map, &pars->token);
        if (pars->token->type == ERROR)
            //ЧИСТИ ЧИСТИ ДА КАК ЭТИМ ЧИСТИТЬ?
            return pars->token;
        if (pars->token->type == LABEL)
        {
            get_next_metion(pars, map, &temp1);
            pars->token->next = create_elem();
            pars->token = pars->token->next;
            if (!check_unique_label(pars, temp1))
                return (0);
        }
        if (pars->token->type != END && pars->token->type != LABEL)
        {
            pars->token->content = get_content(map, pars->token->type);
            if (pars->token->type == INSTRUCTION)
                add_variables(&pars->token, map);
            pars->token->next = create_elem();
            pars->token = pars->token->next;
        }
        if (pars->token->type == END)
            pars->code_size = pars->token->byte;
    }
    pars->token = temp;
    pars->mention = temp1;
    return pars->token;
}
