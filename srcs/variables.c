#include "assem.h"

int     g_line;
int     g_column;
int     g_end;
int     g_byte;
char*   g_link_chars;


void add_variables(t_token** token, char* map)
{
    char*   operation;
    int     flag;

    flag = 1;
    operation = find_operation(map + g_end);
    score_line(map, ft_strlen(operation), 1);
    while (map[g_end] && map[g_end] != '\n' && map[g_end] != '#' && (*token)->type != ERROR)
    {
        (*token)->next = create_elem();
        (*token) = (*token)->next;
        (*token)->type = find_variables(map, token);
        if ((*token)->type != ERROR)
        {
            if ((*token)->type == DIRECT_LABEL || (*token)->type == DIRECT)
                plus2bytes(operation);
            (*token)->content = get_variables(map, (*token)->type);
            if (flag)
            {
                plus_byte(operation);
                flag = 0;
            }
            (*token)->byte = g_byte;
            while (map[g_end] && (map[g_end] == '\t' || map[g_end] == ',' || map[g_end] == ' '))
                score_line(map, 1, 1);
        }
    }
}

t_oken find_variables(char* c, t_token** tok)
{
    while ((c[g_end] == ' ' || c[g_end] == '\t') && c[g_end])
        score_line(c, 1, 1);
    (*tok)->line = g_line;
    (*tok)->column = g_column;
    if (!ft_strcmp1(c + g_end, "%:") && if_label(c + g_end + 2))
        return DIRECT_LABEL;
    else if (!ft_strcmp1(c + g_end, "%") && if_digits(c + g_end + 1))
        return DIRECT;
    else if (!ft_strcmp1(c + g_end, ":") && if_label(c + g_end + 1))
        return INDIRECT_LABEL;
    else if (!ft_strcmp1(c + g_end, "r") && if_register(c + g_end + 1))
        return REGISTER;
    else if (if_digits(c + g_end))
        return INDIRECT;
    return ERROR;
}


char *get_variables(char *map, t_oken token)
{
    char* temp;
    int len;

    len = 0;
    if (token == DIRECT_LABEL)
    {
        g_byte += 2;
        score_line(map, 2, 1);
        while (ft_strchr(g_link_chars, map[g_end + len]))
            len++;
        score_line(map, 1, 0);
        len++;
    }
    else if (token == DIRECT)
    {
        g_byte += 2;
        score_line(map, 1, 1);
        if (map[g_end + len] == '-')
            len++;
        while (ft_isdigit(map[g_end + len]))
            len++;
        temp = ft_itoa(ft_atoi(map + g_end));
        score_line(map, len, 1);
        return temp;
    }
    else if (token == INDIRECT_LABEL)
    {
        g_byte += 2;
        score_line(map, 1, 1);
        while (ft_strchr(g_link_chars, map[g_end + len]))
            len++;
        score_line(map, 1, 0);
        len++;
    }
    else if (token == INDIRECT)
    {
        g_byte += 2;
        if (map[g_end + len] == '-')
            len++;
        while (ft_isdigit(map[g_end + len]))
            len++;
        temp = ft_itoa(ft_atoi(map + g_end));
        score_line(map, len, 1);
        return temp;
    }
    else if (token == REGISTER)
    {
        g_byte++;
        score_line(map, 1, 1);
        while (ft_isdigit(map[g_end + len]))
            len++;
        temp = ft_itoa(ft_atoi(map + g_end));
        score_line(map, len, 1);
        return temp;
    }
    temp = ft_strsub(map, g_end + 1, len - 1);
    score_line(map, len, 1);
    return temp;
}