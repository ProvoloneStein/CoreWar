/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_st_sti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:38:11 by student           #+#    #+#             */
/*   Updated: 2020/04/06 21:18:56 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cmd_st_if_reg(unsigned char *mem,
		int pos, t_cursor *cursor, int t_reg1)
{
	unsigned char	t_reg2;

	t_reg2 = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg2))
		return ;
	cursor->r[t_reg2] = cursor->r[t_reg1];
}

void		cmd_st(unsigned char *mem, t_cursor *cursor,
		t_cmd_info *cmd_info, t_game_info *game_info)
{
	unsigned char	t_reg1;
	short int		t_ind;
	int				pos;

	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	t_reg1 = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg1))
		return ;
	pos += 1;
	pos %= MEM_SIZE;
	if (cmd_info->arg2 == IND_CODE)
	{
		t_ind = get_t_dir2(mem, pos);
		load_from_reg(cursor->r[t_reg1], mem,
				correct_pos(cursor->position + (t_ind % IDX_MOD)));
		if (game_info->color_mem)
			change_color_mem(correct_pos(cursor->position + (t_ind % IDX_MOD)),
					REG_SIZE, game_info->color_mem, cursor->player_id);
	}
	else if (cmd_info->arg2 == REG_CODE)
		cmd_st_if_reg(mem, pos, cursor, t_reg1);
}

static void	cmd_sti_color(t_game_info *game_info, t_cursor *cursor,
		long int arg_info2, long int arg_info3)
{
	if (game_info->color_mem)
		change_color_mem(
			correct_pos(cursor->position + ((arg_info2 + arg_info3) % IDX_MOD)),
			REG_SIZE,
			game_info->color_mem,
			cursor->player_id);
}

void		cmd_sti(unsigned char *mem, t_cursor *cursor,
		t_cmd_info *cmd_info, t_game_info *game_info)
{
	long int		arg_info2;
	long int		arg_info3;
	unsigned char	t_reg;
	int				pos;
	t_mem_cursor	mc;

	mc.cursor = cursor;
	mc.mem = mem;
	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	t_reg = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg))
		return ;
	pos += 1;
	pos %= MEM_SIZE;
	if (!load_arg_info2(&mc, cmd_info->arg2, &arg_info2, &pos))
		return ;
	if (!load_arg_info2(&mc, cmd_info->arg3, &arg_info3, &pos))
		return ;
	load_from_reg(cursor->r[t_reg], mem,
			correct_pos(cursor->position +
			((arg_info2 + arg_info3) % IDX_MOD)));
	cmd_sti_color(game_info, cursor, arg_info2, arg_info3);
}
