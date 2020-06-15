/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 13:02:42 by student           #+#    #+#             */
/*   Updated: 2020/03/25 17:23:01 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cmd_ldi(unsigned char *mem, t_cursor *cursor, t_cmd_info *cmd_info)
{
	long int		arg_info1;
	long int		arg_info2;
	unsigned char	t_reg;
	int				pos;
	t_mem_cursor	mc;

	mc.cursor = cursor;
	mc.mem = mem;
	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	if (!load_arg_info2(&mc, cmd_info->arg1, &arg_info1, &pos))
		return ;
	if (!load_arg_info2(&mc, cmd_info->arg2, &arg_info2, &pos))
		return ;
	t_reg = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg))
		return ;
	cursor->r[t_reg] = get_t_dir4_inplace(mem, correct_pos(
				(cursor->position + ((arg_info1 + arg_info2) % IDX_MOD))
				% MEM_SIZE));
}

void		cmd_lldi(unsigned char *mem, t_cursor *cursor, t_cmd_info *cmd_info)
{
	long int		arg_info1;
	long int		arg_info2;
	unsigned char	t_reg;
	int				pos;
	t_mem_cursor	mc;

	mc.cursor = cursor;
	mc.mem = mem;
	if (LOG_MODE)
		ft_printf("CMD_lldi\n");
	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	if (!load_arg_info2(&mc, cmd_info->arg1, &arg_info1, &pos))
		return ;
	if (!load_arg_info2(&mc, cmd_info->arg2, &arg_info2, &pos))
		return ;
	t_reg = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg))
		return ;
	cursor->r[t_reg] = get_t_dir4(mem,
		(cursor->position + (arg_info1 + arg_info2)) % MEM_SIZE);
}
