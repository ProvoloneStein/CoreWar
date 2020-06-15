/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 15:33:10 by student           #+#    #+#             */
/*   Updated: 2020/03/25 15:33:12 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	free_game(t_cursor **cursor_list,
		t_game_info *game, unsigned char **mem)
{
	if (game->visual.win_field != NULL)
		delwin(game->visual.win_field);
	if (game->visual.win_info != NULL)
		delwin(game->visual.win_info);
	if (game->visual.win_main != NULL)
		endwin();
	if (cursor_list && *cursor_list)
	{
		cursor_list_free(*cursor_list);
		(*cursor_list) = NULL;
	}
	if (mem && *mem)
	{
		free(*mem);
		(*mem) = NULL;
	}
	if (game && game->color_mem)
	{
		free(game->color_mem);
		game->color_mem = NULL;
	}
}

void	free_game_exit(t_game_info *game, unsigned char **mem)
{
	free_game(game->orig_cursor_list, game, mem);
	exit(1);
}
