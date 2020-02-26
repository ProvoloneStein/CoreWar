//
// Created by Greyjoy Aliza on 2020-02-23.
//

#include "assem.h"

char    *find_operation(char* str)
{
    if (!ft_strcmp1(str, "live"))
        return ("live");
    else if (!ft_strcmp1(str, "ldi"))
        return ("ldi");
    else if (!ft_strcmp1(str, "ld"))
        return ("ld");
    else if (!ft_strcmp1(str, "sti"))
        return ("sti");
    else if (!ft_strcmp1(str, "add"))
        return ("add");
    else if (!ft_strcmp1(str, "sub"))
        return ("sub");
    else if (!ft_strcmp1(str, "and"))
        return ("and");
    else if (!ft_strcmp1(str, "or"))
        return ("or");
    else if (!ft_strcmp1(str, "xor"))
        return ("xor");
    else if (!ft_strcmp1(str, "zjmp"))
        return ("zjmp");
    else if (!ft_strcmp1(str, "sti"))
        return ("sti");
    else if (!ft_strcmp1(str, "fork"))
        return ("fork");
    else if (!ft_strcmp1(str, "lldi"))
        return ("lldi");
    else if (!ft_strcmp1(str, "lld"))
        return ("lld");
    else if (!ft_strcmp1(str, "lfork"))
        return ("lfork");
    else if (!ft_strcmp1(str, "aff"))
        return ("aff");
    return 0;
}

char *get_content(char *map, t_oken token, int* end)
{
    char*   link_chars = "abcdefghijklmnopqrstuvwxyz_0123456789";
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
            if (map[start + *end] == '"' && i == 0)
                i = 1;
            else if (i == 0)
                start++;
            if (i == 1)
                len++;
            if (map[start + len + *end] == '"' && i == 1)
                i = 2;
        }
    else if (token == LABEL)
    {
        while (map[*end] != '\n')
            *end = *end - 1;
        while (map[*end + len] != ':')
            len++;
    }
    else if (token == INSTRUCTION)
    {
        temp = find_operation(map + *end);
        *end = *end + ft_strlen(temp);
        return ft_strdup(temp);
    }
    else if (token == DIRECT_LABEL)
    {
        *end = *end + 2;
        while (ft_strchr(link_chars, map[*end + len]))
            len++;
        *end = *end - 1;
        len++;
    }
    else if (token == DIRECT)
    {
        *end = *end + 1;
        while (ft_isdigit(map[*end + len]))
            len++;
        temp = ft_itoa(ft_atoi(map + *end));
        *end = *end + len;
        return temp;
    }
    temp = ft_strsub(map, start + *end + 1, len - 1);
    *end = *end + start + len + 1;
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

t_oken  find_token(char* c, int* end)
{
    while (c[*end])
    {
        if (!ft_strcmp1(c + *end, ".name"))
            return NAME;
        else if (!ft_strcmp1(c + *end, ".comment"))
            return COMMENT;
        else if (!ft_strcmp1(c + *end, "%:"))
            return DIRECT_LABEL;
        else if (!ft_strcmp1(c + *end, "%"))
            return DIRECT;
        else if (!ft_strcmp1(c + *end, ":"))
            return LABEL;
        else if (find_operation(c + *end))
            return INSTRUCTION;
        *end = *end + 1;
    }
    return END;
}

t_token *create_elem()
{
    t_token  *tokenElem;

    tokenElem = (t_token*)malloc(sizeof(t_token));
    tokenElem->type = END;
    tokenElem->byte = 0;
    tokenElem->column = 0;
    tokenElem->content = 0;
    tokenElem->line = 0;
    tokenElem->next = 0;
    return tokenElem;
}

t_token *create_list(char* fd_map)
{
    t_token *temp;
    t_token *list;
    char* map;
    int i;
    int allowedTokens;

    i = 0;
    allowedTokens = 0;
    list = create_elem();
    temp = list;
    read_map(&map, fd_map);
    while (map[i])
    {
        list->type = find_token(map, &i);
        if (list->type != END)
        {
            list->content = get_content(map, list->type, &i);
            list->next = create_elem();
            list = list->next;
        }
    }
    list = temp;
    return list;
}
