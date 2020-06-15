/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_buff_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 11:56:17 by student           #+#    #+#             */
/*   Updated: 2020/03/25 12:04:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			mem_buff_print(unsigned char *mem, int row)
{
	int i;

	i = 0;
	ft_printf("0x0000 : ", i);
	while (i < MEM_SIZE)
	{
		ft_printf("%.2hhx ", mem[i]);
		++i;
		if (i % row == 0 && i < MEM_SIZE)
		{
			ft_printf("\n");
			ft_printf("%#.4x : ", i);
		}
	}
	ft_printf("\n");
}

static int		is_cur_position(t_cursor *cur, int index)
{
	while (cur)
	{
		if (cur->position == index)
			return (1);
		cur = cur->next;
	}
	return (0);
}

static char		*select_color(t_cursor *cursor, int index)
{
	while (cursor)
	{
		if (cursor->position == index)
		{
			if (cursor->player_id == 1)
				return ("\033[41m");
			else if (cursor->player_id == 2)
				return ("\033[45m");
			else if (cursor->player_id == 3)
				return ("\033[44m");
			else if (cursor->player_id == 4)
				return ("\033[42m");
			else if (cursor->player_id == 5)
				return ("\033[46m");
			else if (cursor->player_id == 6)
				return ("\033[43m");
			else
				return ("\033[47m");
		}
		cursor = cursor->next;
	}
	return (NULL);
}

void			mem_buff_print_w_cur(unsigned char *mem,
		t_cursor *cursor, int row)
{
	int i;

	i = 0;
	ft_printf("0x0000 : ", i);
	while (i < MEM_SIZE)
	{
		if (cursor && is_cur_position(cursor, i))
			ft_printf("%s%.2hhx\033[0m ", select_color(cursor, i), mem[i]);
		else
			ft_printf("%.2hhx ", mem[i]);
		++i;
		if (i % row == 0 && i < MEM_SIZE)
		{
			ft_printf("\n");
			ft_printf("%#.4x : ", i);
		}
	}
	ft_printf("\n");
}
