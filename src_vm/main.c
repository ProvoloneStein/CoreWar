/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:04:48 by student           #+#    #+#             */
/*   Updated: 2020/03/25 05:15:41 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	introduce(t_champ champs[MAX_PLAYERS], int n_players)
{
	int i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < n_players)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				i + 1,
				champs[i].sizeof_code, champs[i].name, champs[i].comment);
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_champ			champs[MAX_PLAYERS];
	t_flags			flags;
	t_cursor		*cursor_list;
	unsigned char	*mem;
	int				winner;

	init_champs(champs, &flags, argc, argv);
	if (!(mem = mem_buff_init()))
		check_error("Battlefield", "bad malloc");
	init_vm(mem, champs, flags.count);
	cursor_list = cursor_list_init(flags.count);
	introduce(champs, flags.count);
	if (flags.visual == 1)
		start_game_vis(mem, &cursor_list, &flags, champs);
	else
	{
		winner = start_game(mem, &cursor_list, &flags);
		if (winner != -1)
			ft_printf("winner is player №%d, %s!\n",
					winner, champs[winner - 1].name);
	}
	return (0);
}
