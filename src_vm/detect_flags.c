/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:32:57 by student           #+#    #+#             */
/*   Updated: 2020/04/06 21:19:37 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	count_players(char *tmp, int argc)
{
	int i;
	int count;

	i = 1;
	count = 0;
	while (i < argc)
	{
		if (tmp[i] == 0)
			count++;
		i++;
	}
	if (count == 0 || count > MAX_PLAYERS)
	{
		free(tmp);
		ft_printf((count == 0) ? "No champions\n" : "Too many champions\n");
		exit(1);
	}
	return (count);
}

static void	set_players(t_flags *flags, int argc, char *tmp)
{
	int i;
	int j;
	int count;

	i = 0;
	count = count_players(tmp, argc);
	while (++i < argc)
		if (tmp[i] == 0)
		{
			j = -1;
			while (++j < MAX_PLAYERS)
				if (flags->order[j] == i)
					break ;
			if (j == MAX_PLAYERS)
			{
				j = 0;
				while (flags->order[j] != 0)
					j++;
				flags->order[j] = i;
			}
		}
	flags->count = count;
}

static void	init_flags(t_flags *flags)
{
	int i;

	i = 0;
	flags->for_dump = -1;
	flags->dump_size = 32;
	flags->count = 0;
	while (i < MAX_PLAYERS)
	{
		flags->order[i] = 0;
		i++;
	}
	flags->visual = 0;
	flags->aff = 0;
}

void		detect_flags(t_flags *flags, int argc, char **argv)
{
	int		i;
	char	*tmp;

	i = 1;
	if (!(tmp = ft_strnew(argc)))
		check_error("flags detection:", "malloc error");
	init_flags(flags);
	detect_dump_vis(argc, argv, flags, tmp);
	detect_n(argc, argv, flags, tmp);
	set_players(flags, argc, tmp);
	free(tmp);
}
