/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 15:33:36 by student           #+#    #+#             */
/*   Updated: 2020/04/06 21:22:16 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	init_colors(void)
{
	start_color();
	init_color(COLOR_CYAN, 128, 128, 128);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(5, COLOR_BLACK, COLOR_BLUE);
	init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(8, COLOR_RED, COLOR_BLACK);
	init_pair(9, COLOR_GREEN, COLOR_BLACK);
	init_pair(12, COLOR_RED, COLOR_BLACK);
	init_pair(13, COLOR_GREEN, COLOR_BLACK);
	init_pair(14, COLOR_YELLOW, COLOR_BLACK);
	init_pair(15, COLOR_BLUE, COLOR_BLACK);
	init_pair(16, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(20, COLOR_CYAN, COLOR_BLACK);
}

static void	bad_term(t_game_info *game, unsigned char *mem)
{
	ft_printf("bad terminal size. Rescale, or disable visualisation.\n");
	free_game_exit(game, &mem);
}

static int	create_windows(t_ncurses *visual, t_game_info *game, unsigned char
		*mem)
{
	int height;
	int width;
	int space;

	height = LINES;
	width = 194;
	space = 192 * (LINES - 2);
	if (space < MEM_SIZE)
		bad_term(game, mem);
	if (!(visual->win_field = newwin(height, width, 0, 10)))
		return (1);
	if (!(visual->win_info = newwin(LINES, 50, 0, width + 12)))
		return (1);
	return (0);
}

int			init_ncurses(t_ncurses *visual, t_game_info *game,
		unsigned char *mem)
{
	if (!(visual->win_main = initscr()))
		return (1);
	if (COLS < 40)
		bad_term(game, mem);
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	init_colors();
	if (create_windows(visual, game, mem))
		return (1);
	return (0);
}
