/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:57:13 by student           #+#    #+#             */
/*   Updated: 2020/03/25 12:59:58 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ld_if_t_dir(unsigned char *mem, t_cursor *cursor)
{
	unsigned char	t_reg;
	long int		t_dir;
	int				pos;

	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	t_dir = get_t_dir4(mem, pos);
	pos += 4;
	pos %= MEM_SIZE;
	t_reg = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg))
		return ;
	if (LOG_MODE)
		ft_printf("(dir)reg[%d]=%d\n", t_reg, t_dir);
	cursor->r[t_reg] = t_dir;
	if (cursor->r[t_reg] == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}

void		ld_if_t_indc(unsigned char *mem, t_cursor *cursor)
{
	unsigned char	t_reg;
	short int		t_ind;
	int				pos;
	long int		t_ind_info;

	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	t_ind = get_t_dir2(mem, pos);
	pos += 2;
	pos %= MEM_SIZE;
	t_reg = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg))
		return ;
	t_ind_info = get_t_dir4_inplace(mem,
			correct_pos(cursor->position + (t_ind % IDX_MOD)));
	cursor->r[t_reg] = t_ind_info;
	if (LOG_MODE)
		ft_printf("(ind)reg[%d]=%d\n", t_reg, t_ind_info);
	if (cursor->r[t_reg] == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}

void		lld_if_t_indc(unsigned char *mem, t_cursor *cursor)
{
	unsigned char	t_reg;
	short int		t_ind;
	int				pos;
	long int		t_ind_info;

	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	t_ind = get_t_dir2(mem, pos);
	pos += 2;
	pos %= MEM_SIZE;
	t_reg = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg))
		return ;
	t_ind_info =
		get_t_dir4_inplace(mem, correct_pos(cursor->position + (t_ind)));
	cursor->r[t_reg] = t_ind_info;
	if (LOG_MODE)
		ft_printf("(ind)reg[%d]=%d\n", t_reg, t_ind_info);
	cursor->r[t_reg] = t_ind_info;
	if (cursor->r[t_reg] == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}

void		cmd_ld(unsigned char *mem, t_cursor *cursor, t_cmd_info *cmd_info)
{
	if (LOG_MODE)
		ft_printf("ld\n");
	if (cmd_info->arg1 == DIR_CODE)
		ld_if_t_dir(mem, cursor);
	else if (cmd_info->arg1 == IND_CODE)
		ld_if_t_indc(mem, cursor);
}

void		cmd_lld(unsigned char *mem, t_cursor *cursor, t_cmd_info *cmd_info)
{
	if (LOG_MODE)
		ft_printf("lld\n");
	if (cmd_info->arg1 == DIR_CODE)
		ld_if_t_dir(mem, cursor);
	else if (cmd_info->arg1 == IND_CODE)
		lld_if_t_indc(mem, cursor);
}
