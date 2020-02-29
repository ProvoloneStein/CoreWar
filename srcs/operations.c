#include "assem.h"

int     g_byte;

void    plus2bytes(char *str)
{
    if (!ft_strcmp1(str, "live"))
        g_byte += 2;
    else if (!ft_strcmp1(str, "ld"))
        g_byte += 2;
    else if (!ft_strcmp1(str, "st"))
        g_byte += 2;
    else if (!ft_strcmp1(str, "add"))
        g_byte += 2;
    else if (!ft_strcmp1(str, "sub"))
        g_byte += 2;
    else if (!ft_strcmp1(str, "and"))
        g_byte += 2;
    else if (!ft_strcmp1(str, "or"))
        g_byte += 2;
    else if (!ft_strcmp1(str, "xor"))
        g_byte += 2;
    else if (!ft_strcmp1(str, "lld"))
        g_byte += 2;
    else if (!ft_strcmp1(str, "aff"))
        g_byte += 2;
}