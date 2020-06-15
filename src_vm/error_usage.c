/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 15:32:33 by student           #+#    #+#             */
/*   Updated: 2020/03/25 15:32:44 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_usage(void)
{
	ft_printf("Usage: ./corewar [-aff | (-dump|-d) <num> | -vis] [-n <num>] ");
	ft_printf("<champion.cor> <...>\n");
	ft_printf("-aff        : Print output from \"aff\"\n");
	ft_printf("-dump <num> : Dump memory ");
	ft_printf("(32 octets per line) after <num> cycles and exit\n");
	ft_printf("-d    <num> : Dump memory ");
	ft_printf("(64 octets per line) after <num> cycles and exit\n");
	ft_printf("-vis        : Run visualizer\n");
	ft_printf("-n    <num> : Set <num> of the next player\n");
	exit(0);
}

void	check_error(char *name, char *text)
{
	char *error;

	error = (errno) ? strerror(errno) : text;
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(1);
}

void	free_and_usage(char *tmp)
{
	free(tmp);
	print_usage();
}
