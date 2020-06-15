/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 15:31:00 by student           #+#    #+#             */
/*   Updated: 2020/03/25 15:31:02 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	command_delay(unsigned char cmd)
{
	if (cmd == 0x01 || cmd == 0x04 || cmd == 0x05 || cmd == 0x0d)
		return (10);
	if (cmd == 0x06 || cmd == 0x07 || cmd == 0x08)
		return (6);
	if (cmd == 0x02 || cmd == 0x03)
		return (5);
	if (cmd == 0x09)
		return (20);
	if (cmd == 0x0a || cmd == 0x0b)
		return (25);
	if (cmd == 0x0c)
		return (800);
	if (cmd == 0x0e)
		return (50);
	if (cmd == 0x0f)
		return (1000);
	if (cmd == 0x10)
		return (2);
	return (0);
}

int			do_cycle(unsigned char *mem, t_game_info *game_info)
{
	t_cursor	*cursor_list;

	cursor_list = *(game_info->orig_cursor_list);
	if (!cursor_list)
		return (0);
	while (cursor_list)
	{
		if (cursor_list->delay == 0)
		{
			cursor_list->command = mem[cursor_list->position];
			cursor_list->delay = command_delay(cursor_list->command);
		}
		if (cursor_list->delay > 0)
			cursor_list->delay--;
		if (cursor_list->delay == 0)
			perform_command(mem, cursor_list, game_info);
		cursor_list = cursor_list->next;
	}
	return (1);
}
