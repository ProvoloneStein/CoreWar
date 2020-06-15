/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_zjmp_aff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 13:00:23 by student           #+#    #+#             */
/*   Updated: 2020/06/01 13:26:40 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cmd_zjmp(unsigned char *mem, t_cursor *cursor)
{
	int	t_dir2;

	if (cursor->carry == 1)
	{
		t_dir2 = get_t_dir2(mem, cursor->position) % IDX_MOD;
		if (LOG_MODE)
			ft_printf("zjmp Yes! %d + %d\n", cursor->position, t_dir2);
		cursor_change_position(cursor, t_dir2);
		if (LOG_MODE)
			ft_printf("_ = %d\n", cursor->position);
		return (0);
	}
	else
	{
		if (LOG_MODE)
			ft_printf("zjmp No!\n");
		return (3);
	}
}

void		cmd_aff(unsigned char *mem, t_cursor *cursor, t_game_info *info)
{
	int				pos;
	unsigned char	t_reg;

	if (LOG_MODE)
		ft_printf("CMD_aff\n");
	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	t_reg = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg))
		return ;
	if (info->is_aff_flag)
	{
		ft_putchar((char)cursor->r[t_reg]);
		ft_putchar('\n');
	}
}
