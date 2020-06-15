/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_or_xor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 13:12:13 by student           #+#    #+#             */
/*   Updated: 2020/03/25 17:17:52 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cmd_and(unsigned char *mem, t_cursor *cursor, t_cmd_info *cmd_info)
{
	long int		arg_info1;
	long int		arg_info2;
	unsigned char	t_reg;
	int				pos;
	t_mem_cursor	mc;

	mc.cursor = cursor;
	mc.mem = mem;
	if (LOG_MODE)
		ft_printf("CMD_and\n");
	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	if (!load_arg_info(&mc, cmd_info->arg1, &arg_info1, &pos))
		return ;
	if (!load_arg_info(&mc, cmd_info->arg2, &arg_info2, &pos))
		return ;
	t_reg = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg))
		return ;
	cursor->r[t_reg] = arg_info1 & arg_info2;
	if (cursor->r[t_reg] == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}

void		cmd_or(unsigned char *mem, t_cursor *cursor, t_cmd_info *cmd_info)
{
	long int		arg_info1;
	long int		arg_info2;
	unsigned char	t_reg;
	int				pos;
	t_mem_cursor	mc;

	mc.cursor = cursor;
	mc.mem = mem;
	if (LOG_MODE)
		ft_printf("CMD_or\n");
	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	if (!load_arg_info(&mc, cmd_info->arg1, &arg_info1, &pos))
		return ;
	if (!load_arg_info(&mc, cmd_info->arg2, &arg_info2, &pos))
		return ;
	t_reg = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg))
		return ;
	cursor->r[t_reg] = arg_info1 | arg_info2;
	if (cursor->r[t_reg] == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}

void		cmd_xor(unsigned char *mem, t_cursor *cursor, t_cmd_info *cmd_info)
{
	long int		arg_info1;
	long int		arg_info2;
	unsigned char	t_reg;
	int				pos;
	t_mem_cursor	mc;

	mc.cursor = cursor;
	mc.mem = mem;
	if (LOG_MODE)
		ft_printf("CMD_xor\n");
	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	if (!load_arg_info(&mc, cmd_info->arg1, &arg_info1, &pos))
		return ;
	if (!load_arg_info(&mc, cmd_info->arg2, &arg_info2, &pos))
		return ;
	t_reg = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg))
		return ;
	cursor->r[t_reg] = arg_info1 ^ arg_info2;
	if (cursor->r[t_reg] == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}
