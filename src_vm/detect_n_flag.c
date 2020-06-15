/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_n_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 15:31:24 by student           #+#    #+#             */
/*   Updated: 2020/03/25 15:31:34 by student          ###   ########.fr       */
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

static void	set_n(t_flags *flags, char *tmp, int num, int i)
{
	if (num <= MAX_PLAYERS && num >= 1)
	{
		if (flags->order[num - 1] == 0)
			flags->order[num - 1] = i + 2;
		else
			free_and_usage(tmp);
	}
	tmp[i] = 1;
	tmp[i + 1] = 1;
}

void		detect_n(int argc, char **argv, t_flags *flags, char *tmp)
{
	int i;
	int num;

	i = 0;
	num = 0;
	while (++i < argc)
	{
		if (tmp[i] != 0)
			continue ;
		if (ft_strequ(argv[i], "-n"))
		{
			if (i + 2 < argc && check_param(argv[i + 1]))
			{
				num = ft_atoi(argv[i + 1]);
				set_n(flags, tmp, num, i);
			}
			i++;
		}
	}
}
