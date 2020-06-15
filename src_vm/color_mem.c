/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 13:02:21 by student           #+#    #+#             */
/*   Updated: 2020/03/25 13:02:31 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char	*color_mem_init(int n_players, t_champ *champs)
{
	int				i;
	int				pos;
	unsigned char	*color_mem;

	if (!(color_mem = mem_buff_init()))
		return (NULL);
	i = 0;
	pos = 0;
	while (i < n_players)
	{
		change_color_mem(pos, champs[i].sizeof_code, color_mem, i + 1);
		pos += MEM_SIZE / n_players;
		i++;
	}
	return (color_mem);
}

void			change_color_mem(int place, int size,
		unsigned char *c_mem, unsigned char player_color)
{
	int	start;
	int	end;

	start = correct_pos(place);
	end = correct_pos(place + size);
	while (start != end)
	{
		c_mem[start] = player_color;
		++start;
		start %= MEM_SIZE;
	}
}
