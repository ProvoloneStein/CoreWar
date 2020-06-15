/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cmd_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 15:35:27 by student           #+#    #+#             */
/*   Updated: 2020/03/25 15:35:29 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	number_of_args(unsigned char cmd)
{
	if (cmd == 0x02 || cmd == 0x0d)
		return (2);
	else if (cmd == 0x03)
		return (2);
	else if (cmd == 0x05 || cmd == 0x04)
		return (3);
	else if (cmd == 0x06 || cmd == 0x07 || cmd == 0x08)
		return (3);
	else if (cmd == 0x0a || cmd == 0x0e)
		return (3);
	else if (cmd == 0x0b)
		return (3);
	else if (cmd == 0x10)
		return (1);
	return (1);
}

static int	is_right_args(unsigned char cmd,
			unsigned char a1, unsigned char a2, unsigned char a3)
{
	if ((cmd == 0x02 || cmd == 0x0d) &&
			(a1 == DIR_CODE || a1 == IND_CODE) && a2 == REG_CODE)
		return (2);
	else if (cmd == 0x03 && (a2 == REG_CODE || a2 == IND_CODE)
			&& a1 == REG_CODE)
		return (2);
	else if ((cmd == 0x05 || cmd == 0x04) && a1 == REG_CODE
			&& a2 == REG_CODE && a3 == REG_CODE)
		return (3);
	else if ((cmd == 0x06 || cmd == 0x07 || cmd == 0x08) &&
			a1 != 0 && a2 != 0 && a3 == REG_CODE)
		return (3);
	else if ((cmd == 0x0a || cmd == 0x0e) && a1 != 0 &&
			(a2 == REG_CODE || a2 == DIR_CODE) && a3 == REG_CODE)
		return (3);
	else if (cmd == 0x0b && a1 == REG_CODE &&
			a2 != 0 && (a3 == REG_CODE || a3 == DIR_CODE))
		return (3);
	else if (cmd == 0x10 && a1 == REG_CODE)
		return (1);
	else
		return (0);
}

static int	find_t_dir_size(unsigned char cmd)
{
	if (cmd >= 0x01 && cmd <= 0x08)
		return (4);
	if (cmd == 0x0d)
		return (4);
	if (cmd == 0x10)
		return (4);
	return (2);
}

int			load_cmd_info(t_cmd_info *info,
			unsigned char *mem, t_cursor *cursor)
{
	int	temp_pos;

	temp_pos = cursor->position;
	info->id = cursor->command;
	temp_pos += 1;
	temp_pos %= MEM_SIZE;
	info->arg1 = (mem[temp_pos] & 0xc0) >> 6;
	info->arg2 = (mem[temp_pos] & 0x30) >> 4;
	info->arg3 = (mem[temp_pos] & 0xc) >> 2;
	info->dir_size = find_t_dir_size(info->id);
	info->n_args = number_of_args(info->id);
	return (is_right_args(info->id, info->arg1, info->arg2, info->arg3));
}
