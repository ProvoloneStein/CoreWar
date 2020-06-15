/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 18:53:42 by student           #+#    #+#             */
/*   Updated: 2020/03/27 18:53:45 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		draw(t_game_info *game)
{
	set_field(game->visual.win_field, *(game->orig_cursor_list),
			game->visual.mem, game->color_mem);
	set_info(game->visual.win_info, game, game->visual.champs);
}
