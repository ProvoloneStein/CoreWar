/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_shift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 15:30:24 by student           #+#    #+#             */
/*   Updated: 2020/03/25 15:30:26 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	arg_size(unsigned char arg, unsigned char size)
{
	if (arg == DIR_CODE)
		return (size);
	else if (arg == REG_CODE)
		return (1);
	else if (arg == IND_CODE)
		return (2);
	return (0);
}

int			count_shift(t_cmd_info *info)
{
	int	total;

	total = 2 + arg_size(info->arg1, info->dir_size);
	if (info->n_args >= 2)
		total += arg_size(info->arg2, info->dir_size);
	if (info->n_args == 3)
		total += arg_size(info->arg3, info->dir_size);
	return (total);
}
