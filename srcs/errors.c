/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 22:43:04 by pstein            #+#    #+#             */
/*   Updated: 2020/03/16 17:49:01 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"

int		errors_handler(int i, int x, int y)
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
		ft_printf("[%i, %i] there is more params that is needed. Isn't it?\n",
				x, y);
	else if (i == 5)
		ft_printf("[%i, %i] not enough params in this function\n", x, y);
	else if (i == 6)
		ft_printf(
				"[%i, %i] Your champ should do anything.Why he has no code?\n",
				x, y);
	else if (i == 7)
		ft_printf("[%i, %i] Your champ can't do this instrunction\n", x, y);
	exit(0);
}

int		err_handler(int i, int y, int x)
{
	if (i == 0)
		ft_printf("Syntax error - Perhaps you forgot to end with a newline?\n");
	else if (i == 1)
		ft_printf("Lexical error at [%i,%i]\n", x, y);
	else if (i == 2)
		ft_printf("Labels got same names\n");
	else if (i == 3)
		ft_printf("Syntax error at token [TOKEN][%i:%i]\n", x, y);
	else if (i == 4)
		ft_printf("Can't open this file\n");
	exit(0);
}
