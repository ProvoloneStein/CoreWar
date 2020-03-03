#include "assem.h"

int     g_byte;

void    plus2bytes(char *str)
{
    if (!ft_strcmp(str, "live"))
        g_byte += 2;
    else if (!ft_strcmp(str, "ld"))
        g_byte += 2;
    else if (!ft_strcmp(str, "st"))
        g_byte += 2;
    else if (!ft_strcmp(str, "add"))
        g_byte += 2;
    else if (!ft_strcmp(str, "sub"))
        g_byte += 2;
    else if (!ft_strcmp(str, "and"))
        g_byte += 2;
    else if (!ft_strcmp(str, "or"))
        g_byte += 2;
    else if (!ft_strcmp(str, "xor"))
        g_byte += 2;
    else if (!ft_strcmp(str, "lld"))
        g_byte += 2;
    else if (!ft_strcmp(str, "aff"))
        g_byte += 2;
}

void    plus_byte(char *str)
{
    if (!ft_strcmp(str, "ldi"))
        g_byte += 1;
    else if (!ft_strcmp(str, "ld"))
        g_byte += 1;
    else if (!ft_strcmp(str, "sti"))
        g_byte += 1;
    else if (!ft_strcmp(str, "st"))
        g_byte += 1;
    else if (!ft_strcmp(str, "add"))
        g_byte += 1;
    else if (!ft_strcmp(str, "sub"))
        g_byte += 1;
    else if (!ft_strcmp(str, "and"))
        g_byte += 1;
    else if (!ft_strcmp(str, "or"))
        g_byte += 1;
    else if (!ft_strcmp(str, "xor"))
        g_byte += 1;
    else if (!ft_strcmp(str, "lldi"))
        g_byte += 1;
    else if (!ft_strcmp(str, "lld"))
        g_byte += 1;
    else if (!ft_strcmp(str, "aff"))
        g_byte += 1;
}

int    check_unique_label(t_pars* pars, t_ment* ment)
{
    t_ment* temp1;
    t_ment* temp2;

    temp1 = ment;
    temp2 = ment->next;
    while (temp1->next)
    {
        while (temp2)
        {
            if (!ft_strcmp(temp1->name, temp2->name))
            {
                pars->token = create_elem();
                // ЧИСТИ ЧИСТИ ЧИСТИ ДА КАК ЭТИМ ЧИСТИТЬ?
                pars->token->type = ERROR;
                return (0);
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
        temp2 = temp1->next;
    }
    return (1);
}