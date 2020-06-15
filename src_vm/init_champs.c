/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:24:07 by student           #+#    #+#             */
/*   Updated: 2020/03/25 12:24:11 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_champs(t_champ *champs, t_flags *flags, int argc, char **argv)
{
	int	i;
	int	j;

	if (argc == 1)
		print_usage();
	detect_flags(flags, argc, argv);
	i = 0;
	while (i < flags->count)
	{
		j = 0;
		while (j < MAX_PLAYERS)
		{
			if (flags->order[j] != 0)
			{
				fill_champ(&champs[i], argv[flags->order[j]]);
				champs[i].num = i + 1;
				i++;
			}
			j++;
		}
	}
}
