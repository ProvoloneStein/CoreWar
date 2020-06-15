/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_with_vis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:08:36 by student           #+#    #+#             */
/*   Updated: 2020/06/01 13:33:25 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	init_game(t_game_info *game,
		t_cursor **cursor_list, unsigned char *mem, t_champ *champs)
{
	game->current_cycle = 1;
	game->cycles_to_die = CYCLE_TO_DIE;
	game->check_counter = 1;
	game->last_alive = (*cursor_list)->player_id;
	game->orig_cursor_list = cursor_list;
	game->live_count = 0;
	game->n_cursors = game->n_players;
	game->next_cur_id = game->n_players + 1;
	game->is_aff_flag = 0;
	if (!(game->color_mem = color_mem_init(game->n_players, champs)))
		free_game_exit(game, &mem);
	game->visual.pause = 1;
	game->visual.game_over = 0;
	game->visual.win_main = NULL;
	game->visual.win_field = NULL;
	game->visual.win_info = NULL;
	game->visual.last_press = -1;
	game->visual.champs = champs;
	game->visual.mem = mem;
	game->visual.cursor_list = cursor_list;
}

static void	re_name(t_champ *champs, int n)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (i < n)
	{
		s = champs[i].name;
		j = 0;
		while (s[j])
		{
			if (s[j] == '\t' || s[j] == '\n' || s[j] == '\v')
				s[j] = ' ';
			j++;
		}
		i++;
	}
}

static int	check_pause(t_game_info *game)
{
	if (game->visual.last_press == ' ')
		game->visual.pause = !(game->visual.pause);
	if (game->n_cursors == 0)
	{
		game->visual.pause = 1;
		game->visual.game_over = 1;
	}
	draw(game);
	if (game->visual.pause == 1)
		return (1);
	else
		return (0);
}

static void	check_cycles_to_die(t_game_info *game)
{
	if (game->cycles_to_die <= 0 || game->check_counter == game->cycles_to_die)
	{
		do_check(game->orig_cursor_list, &(game->cycles_to_die), game);
		game->live_count = 0;
		game->check_counter = 0;
	}
	++game->check_counter;
	++game->current_cycle;
}

int			start_game_vis(unsigned char *mem, t_cursor **cursor_list,
		t_flags *flags, t_champ *champs)
{
	t_game_info	game;

	game.n_players = flags->count;
	re_name(champs, game.n_players);
	init_game(&game, cursor_list, mem, champs);
	if (init_ncurses(&(game.visual), &game, mem))
		free_game_exit(&game, &mem);
	draw(&game);
	while ((game.visual.last_press = getch()) != 27)
	{
		if (check_pause(&game))
			continue;
		if (do_cycle(game.visual.mem, &game) == 0)
			break ;
		check_cycles_to_die(&game);
		draw(&game);
	}
	free_game(cursor_list, &game, &mem);
	return (0);
}
