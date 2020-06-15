/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:27:57 by student           #+#    #+#             */
/*   Updated: 2020/03/25 12:31:27 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	do_cmd_w_args(
		unsigned char *mem,
		t_cursor *cursor,
		t_cmd_info *info,
		t_game_info *game_info)
{
	if (cursor->command == 0x02)
		(cmd_ld(mem, cursor, info));
	else if (cursor->command == 0x03)
		(cmd_st(mem, cursor, info, game_info));
	else if (cursor->command == 0x04)
		(cmd_add(mem, cursor));
	else if (cursor->command == 0x05)
		(cmd_sub(mem, cursor));
	else if (cursor->command == 0x06)
		(cmd_and(mem, cursor, info));
	else if (cursor->command == 0x07)
		(cmd_or(mem, cursor, info));
	else if (cursor->command == 0x08)
		(cmd_xor(mem, cursor, info));
	else if (cursor->command == 0x0a)
		(cmd_ldi(mem, cursor, info));
	else if (cursor->command == 0x0b)
		(cmd_sti(mem, cursor, info, game_info));
	else if (cursor->command == 0x0d)
		(cmd_lld(mem, cursor, info));
	else if (cursor->command == 0x0e)
		(cmd_lldi(mem, cursor, info));
	else if (cursor->command == 0x10)
		(cmd_aff(mem, cursor, game_info));
	return (count_shift(info));
}

int	do_cmd_no_args(unsigned char *mem, t_cursor *cursor, t_game_info *game_info)
{
	if (LOG_MODE)
		ft_printf("(%d) ", cursor->cursor_id);
	if (cursor->command == 0x01)
		return (cmd_live(mem, cursor, game_info));
	else if (cursor->command == 0x09)
		return (cmd_zjmp(mem, cursor));
	else if (cursor->command == 0x0c)
		return (cmd_fork(mem, cursor, game_info));
	else if (cursor->command == 0x0f)
		return (cmd_lfork(mem, cursor, game_info));
	return (1);
}
