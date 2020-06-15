/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 13:09:47 by student           #+#    #+#             */
/*   Updated: 2020/03/25 13:11:52 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		is_dead(t_cursor *cursor, int cycles_to_die, int current_cycle)
{
	if (cycles_to_die <= 0)
		return (1);
	else if (((current_cycle - cycles_to_die) >= cursor->last_live_cycle))
		return (1);
	return (0);
}

void	check_cursor_list(t_cursor **cursor_list,
		int cycles_to_die, t_game_info *game)
{
	t_cursor	*prev;
	t_cursor	*tmp;

	prev = NULL;
	tmp = NULL;
	if (cursor_list)
		tmp = *cursor_list;
	while (tmp)
	{
		if (is_dead(tmp, cycles_to_die, game->current_cycle))
		{
			cursor_list_del(cursor_list, &tmp, prev);
			--game->n_cursors;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

int		do_check(t_cursor **cursor_list, int *cycles_to_die, t_game_info *game)
{
	static int	n_checks = 0;

	check_cursor_list(cursor_list, *cycles_to_die, game);
	if (game->live_count >= NBR_LIVE)
	{
		*cycles_to_die -= CYCLE_DELTA;
		n_checks = 0;
	}
	else
		++n_checks;
	if (n_checks >= MAX_CHECKS)
	{
		*cycles_to_die -= CYCLE_DELTA;
		n_checks = 0;
	}
	if (cursor_list && *cursor_list == NULL)
		return (0);
	return (1);
}
