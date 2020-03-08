#include "assem.h"

int     if_name(char* str)
{
    int     i;

    i = 0;
    if (ft_strcmp1(str, ".name"))
        return (0);
    i = i + ft_strlen(".name");
    while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
        i++;
    if (!str[i] || str[i] != '"')
        return (0);
    i++;
    while (str[i] && str[i] != '"')
        i++;
    if (str[i])
        return (1);
    return (0);
}

int     if_comment(char* str)
{
    int     i;

    i = 0;
    if (ft_strcmp1(str, ".comment"))
        return (0);
    i = i + ft_strlen(".comment");
    while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
        i++;
    if (!str[i] || str[i] != '"')
        return (0);
    i++;
    while (str[i] && str[i] != '"')
        i++;
    if (str[i])
        return (1);
    return (0);
}

int     if_operation(char* str)
{
    char*   temp;
    int     i;

    i = 0;
    temp = find_operation(str);
    if (!temp)
        return (0);
    i = ft_strlen(temp);
    if (str[i] == ' ' || str[i] == '\t' || str[i] == '%')
        return (1);
    return (0);
}

int     check_map(char* map)
{
    int     i;

    i = 0;
    while (map[i])
        i++;
    while (i > 0 && map[i] != '\n')
        i--;
    i++;
    while (map[i] == ' ' || map[i] == '\t')
        i++;
    if (!map[i] || map[i] == '#')
        return (1);
    return (0);
}