/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 13:08:24 by student           #+#    #+#             */
/*   Updated: 2020/03/25 13:09:03 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cmd_add(unsigned char *mem, t_cursor *cursor)
{
	unsigned char	t_reg1;
	unsigned char	t_reg2;
	unsigned char	t_reg3;
	int				pos;

	if (LOG_MODE)
		ft_printf("CMD_add\n");
	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	t_reg1 = get_t_reg(mem, pos);
	pos += 1;
	pos %= MEM_SIZE;
	t_reg2 = get_t_reg(mem, pos);
	pos += 1;
	pos %= MEM_SIZE;
	t_reg3 = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg1) || !is_right_reg(t_reg2) || !is_right_reg(t_reg3))
		return ;
	cursor->r[t_reg3] = cursor->r[t_reg2] + cursor->r[t_reg1];
	if (cursor->r[t_reg3] == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}

void		cmd_sub(unsigned char *mem, t_cursor *cursor)
{
	unsigned char	t_reg1;
	unsigned char	t_reg2;
	unsigned char	t_reg3;
	int				pos;

	if (LOG_MODE)
		ft_printf("CMD_sub\n");
	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	t_reg1 = get_t_reg(mem, pos);
	pos += 1;
	pos %= MEM_SIZE;
	t_reg2 = get_t_reg(mem, pos);
	pos += 1;
	pos %= MEM_SIZE;
	t_reg3 = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg1) || !is_right_reg(t_reg2) || !is_right_reg(t_reg3))
		return ;
	cursor->r[t_reg3] = cursor->r[t_reg1] - cursor->r[t_reg2];
	if (cursor->r[t_reg3] == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}
