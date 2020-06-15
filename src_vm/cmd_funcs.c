/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 13:14:05 by student           #+#    #+#             */
/*   Updated: 2020/03/25 13:19:21 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			is_right_reg(unsigned char reg)
{
	if (reg >= 1 && reg <= REG_NUMBER)
		return (1);
	return (0);
}

int			correct_pos(int pos)
{
	pos %= MEM_SIZE;
	if (pos < 0)
		pos = MEM_SIZE + pos;
	return (pos);
}
