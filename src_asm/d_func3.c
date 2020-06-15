/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_func3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 15:21:52 by pstein            #+#    #+#             */
/*   Updated: 2020/03/14 20:52:21 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassem.h"

char	*ft_d_sti(t_read *reader)
{
	char *line;

	line = "\nsti ";
	reader->i += 1;
	reader->arg_types = reader->code[reader->i];
	reader->i += 1;
	line = ft_strplus(line, print_arg(reader, 2, 3, 1), 0, 1);
	line = ft_strplus(line, ", ", 1, 0);
	line = ft_strplus(line, print_arg(reader, 2, 7, 2), 1, 1);
	line = ft_strplus(line, ", ", 1, 0);
	line = ft_strplus(line, print_arg(reader, 2, 5, 3), 1, 1);
	return (line);
}

char	*ft_d_fork(t_read *reader)
{
	char *line;

	line = "\nfork ";
	reader->i += 1;
	line = ft_strplus(line, print_dir(reader, 2), 0, 1);
	return (line);
}

char	*ft_d_lld(t_read *reader)
{
	char	*line;

	line = "\nlld ";
	reader->i += 1;
	reader->arg_types = reader->code[reader->i];
	reader->i += 1;
	line = ft_strplus(line, print_arg(reader, 4, 4, 1), 0, 1);
	line = ft_strplus(line, ", ", 1, 0);
	line = ft_strplus(line, print_arg(reader, 4, 3, 2), 1, 1);
	print_arg(reader, 4, 0, 3);
	return (line);
}

char	*ft_d_lldi(t_read *reader)
{
	char	*line;

	line = "\nlldi ";
	reader->i += 1;
	reader->arg_types = reader->code[reader->i];
	reader->i += 1;
	line = ft_strplus(line, print_arg(reader, 2, 7, 1), 0, 1);
	line = ft_strplus(line, ", ", 1, 0);
	line = ft_strplus(line, print_arg(reader, 2, 5, 2), 1, 1);
	line = ft_strplus(line, ", ", 1, 0);
	line = ft_strplus(line, print_arg(reader, 2, 3, 3), 1, 1);
	return (line);
}

char	*ft_d_lfork(t_read *reader)
{
	char	*line;

	line = "\nlfork ";
	reader->i += 1;
	line = ft_strplus(line, print_dir(reader, 2), 0, 1);
	return (line);
}
