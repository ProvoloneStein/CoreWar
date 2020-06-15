/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_dump_vis_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:32:54 by student           #+#    #+#             */
/*   Updated: 2020/03/25 04:59:46 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	check_param(char *argv)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(argv);
	if (len > 10)
		return (0);
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (0);
		i++;
	}
	if (len == 10)
	{
		if (ft_strcmp(argv, "2147483647") > 0)
			return (0);
	}
	return (1);
}

static void	set_dump(t_flags *flags, char **argv, int i, char *tmp)
{
	flags->for_dump = ft_atoi(argv[i + 1]);
	flags->dump_size = (argv[i][2] == 'u') ? 32 : 64;
	tmp[i] = 1;
	tmp[i + 1] = 1;
	i++;
}

void		detect_dump_vis(int argc, char **argv, t_flags *flags, char *tmp)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			if (ft_strequ(argv[i], "-dump") || ft_strequ(argv[i], "-d"))
			{
				if (i + 1 < argc && check_param(argv[i + 1]))
					set_dump(flags, argv, i, tmp);
			}
			else if (ft_strequ(argv[i], "-vis"))
			{
				flags->visual = 1;
				tmp[i] = 1;
			}
			else if (ft_strequ(argv[i], "-aff") || ft_strequ(argv[i], "-a"))
			{
				flags->aff = 1;
				tmp[i] = 1;
			}
		}
		i++;
	}
}
