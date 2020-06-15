/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 18:56:23 by student           #+#    #+#             */
/*   Updated: 2020/04/06 11:24:51 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	print_players(WINDOW *info, int n, t_champ *champs,
		t_game_info *game)
{
	int i;
	int color;

	i = 0;
	while (i < game->n_players)
	{
		color = (i >= 4) ? 6 : i + 2;
		wattron(info, COLOR_PAIR(color));
		mvwprintw(info, n += 3, 2,
				"Player #%d, %s", champs[i].num, champs[i].name);
		i++;
		wattroff(info, COLOR_PAIR(color));
	}
	mvwprintw(info, n += 3, 2, "Last alive: #%d as %s",
			game->last_alive, champs[game->last_alive - 1].name);
	return (n);
}

static void	game_over(WINDOW *info, t_game_info *game, int n, t_champ *champs)
{
	int color;

	if (game->visual.game_over == 1)
	{
		color = (game->last_alive >= 6) ? 6 : game->last_alive + 1;
		wattron(info, COLOR_PAIR(color));
		mvwprintw(info, n += 2, 2, "Winner: Player #%d, %s\n",
				champs[game->last_alive - 1].num,
				champs[game->last_alive - 1].name);
		wattroff(info, COLOR_PAIR(color));
	}
}

void		set_info(WINDOW *info, t_game_info *game, t_champ *champs)
{
	int n;

	n = 1;
	werase(info);
	wattron(info, (game->visual.pause == 0) ? COLOR_PAIR(9) : COLOR_PAIR(8));
	mvwprintw(info, n, 2, (game->visual.pause == 0) ? "Running" : "Paused ");
	wattroff(info, (game->visual.pause == 0) ? COLOR_PAIR(3) : COLOR_PAIR(2));
	mvwprintw(info, n += 2, 2, "Cycle: %d", game->current_cycle);
	mvwprintw(info, n += 2, 2, "Cursors: %d", game->n_cursors);
	n += print_players(info, n, champs, game);
	mvwprintw(info, n += 2, 2, "Cycles_to_die: %d", game->cycles_to_die);
	mvwprintw(info, n += 2, 2, "Lives: %d", game->live_count);
	mvwprintw(info, n += 2, 2, "Cycles_to_check: %d",
			game->cycles_to_die - game->check_counter);
	game_over(info, game, n, champs);
	box(info, 0, 0);
	wrefresh(info);
}
