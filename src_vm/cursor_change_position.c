/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_change_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 13:02:01 by student           #+#    #+#             */
/*   Updated: 2020/03/25 13:02:02 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cursor_change_position(t_cursor *list, int shift)
{
	if (list)
	{
		list->position += shift;
		list->position %= MEM_SIZE;
		if (list->position < 0)
			list->position = MEM_SIZE + list->position;
	}
}
