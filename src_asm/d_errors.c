/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 15:58:26 by pstein            #+#    #+#             */
/*   Updated: 2020/03/15 20:16:36 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassem.h"

char	*d_errors(int error)
{
	if (error == 1)
		ft_printf("No such file or can't open\n");
	else if (error == 2)
		ft_printf("Can't make file\n");
	else if (error == 3)
		ft_printf("Incorrect champ code\n");
	else if (error == 4)
		ft_printf("Incorrect MAGIC\n");
	else if (error == 5)
		ft_printf("Incorrect command len\n");
	else if (error == 6)
		ft_printf("I'm sorry I'm tired and work incorrectly\n");
	exit(1);
}
