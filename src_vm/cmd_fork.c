/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 13:19:37 by student           #+#    #+#             */
/*   Updated: 2020/03/25 05:17:46 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cursor_copy_info(t_cursor *src, t_cursor *dst)
{
	int	i;

	i = 1;
	while (i <= REG_NUMBER)
	{
		dst->r[i] = src->r[i];
		++i;
	}
	dst->carry = src->carry;
	dst->last_live_cycle = src->last_live_cycle;
}

int			cmd_fork(unsigned char *mem, t_cursor *cursor, t_game_info *info)
{
	t_cursor	*new;

	new = cursor_list_new(
			correct_pos(cursor->position +
				(get_t_dir2(mem, cursor->position) % IDX_MOD)),
			info->next_cur_id,
			cursor->player_id);
	if (new == NULL)
		free_game_exit(info, &mem);
	cursor_copy_info(cursor, new);
	*(info->orig_cursor_list) = cursor_list_add(*(info->orig_cursor_list), new);
	++info->next_cur_id;
	++info->n_cursors;
	return (3);
}

int			cmd_lfork(unsigned char *mem, t_cursor *cursor, t_game_info *info)
{
	t_cursor	*new;

	new = cursor_list_new(
			correct_pos(get_t_dir2(mem, cursor->position) + cursor->position),
			info->next_cur_id,
			cursor->player_id);
	if (new == NULL)
		free_game_exit(info, &mem);
	cursor_copy_info(cursor, new);
	*(info->orig_cursor_list) = cursor_list_add(*(info->orig_cursor_list), new);
	++info->next_cur_id;
	++info->n_cursors;
	return (3);
}
