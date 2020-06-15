/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 15:36:40 by student           #+#    #+#             */
/*   Updated: 2020/03/25 15:36:42 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	is_right_command(unsigned char command)
{
	if (command >= 0x01 && command <= 0x10)
		return (1);
	return (0);
}

static int	is_args_type_req(unsigned char cmd)
{
	if (cmd == 0x01 || cmd == 0x09 || cmd == 0x0c || cmd == 0x0f)
		return (0);
	return (1);
}

void		perform_command(unsigned char *mem,
			t_cursor *cursor, t_game_info *game_info)
{
	t_cmd_info	cmd_info;

	if (!is_right_command(cursor->command))
	{
		cursor_change_position(cursor, 1);
	}
	else if (!is_args_type_req(cursor->command))
	{
		cursor_change_position(cursor, do_cmd_no_args(mem, cursor, game_info));
	}
	else if (load_cmd_info(&cmd_info, mem, cursor) != 0)
	{
		cursor_change_position(cursor,
				do_cmd_w_args(mem, cursor, &cmd_info, game_info));
	}
	else
	{
		cursor_change_position(cursor, count_shift(&cmd_info));
	}
}
