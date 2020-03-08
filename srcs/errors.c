/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 22:43:04 by pstein            #+#    #+#             */
/*   Updated: 2020/03/01 18:15:32 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"

int errors_handler(int i, int x, int y)
{
    if (i == 0)
        ft_printf("[%i, %i] token read error\n", x, y);
    else if (i == 1)
        ft_printf("[%i, %i] not a valid mention\n", x, y);
    else if (i == 2)
        ft_printf("[%i, %i] not a valid function arg\n", x, y);
    else if (i == 3)
        ft_printf("[%i, %i] comment or name error\n", x, y);
    else if (i == 4)
        ft_printf("[%i, %i] there is more params that is needed. Isn't it\n?", x, y);
    else if (i == 5)
        ft_printf("[%i, %i] not enough params in this function\n", x, y);
    return (0);
}

void    err_handler(int i, int y, int x)
{
    if (i == 0)
        ft_printf("Syntax error - unexpected end of input (Perhaps you forgot to end with a newline ?)");
    else if (i == 1)
        ft_printf("Lexical error at [%i,%i]", x, y);
    else if (i == 2)
        ft_printf("Labels got same names");
    else if (i == 3)
        ft_printf("Syntax error at token [TOKEN][%i:%i]", x, y);
    exit(0);
}