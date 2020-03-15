/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_func2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 15:21:33 by pstein            #+#    #+#             */
/*   Updated: 2020/03/15 14:21:25 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassem.h"

char	*ft_d_and(t_read *reader)
{
	char	*line;

	line = "\nand ";
	reader->i += 1;
	reader->arg_types = reader->code[reader->i];
	reader->i += 1;
	line = ft_strplus(line, print_arg(reader, 4, 7, 1), 0, 1);
	line = ft_strplus(line, ", ", 1, 0);
	line = ft_strplus(line, print_arg(reader, 4, 7, 2), 1, 1);
	line = ft_strplus(line, ", ", 1, 0);
	line = ft_strplus(line, print_arg(reader, 4, 3, 3), 1, 1);
	return (line);
}

char	*ft_d_or(t_read *reader)
{
	char	*line;

	line = "\nor ";
	reader->i += 1;
	reader->arg_types = reader->code[reader->i];
	reader->i += 1;
	line = ft_strplus(line, print_arg(reader, 4, 7, 1), 0, 1);
	line = ft_strplus(line, ", ", 1, 0);
	line = ft_strplus(line, print_arg(reader, 4, 7, 2), 1, 1);
	line = ft_strplus(line, ", ", 1, 0);
	line = ft_strplus(line, print_arg(reader, 4, 3, 3), 1, 1);
	return (line);
}

char	*ft_d_xor(t_read *reader)
{
	char	*line;

	line = "\nxor ";
	reader->i += 1;
	reader->arg_types = reader->code[reader->i];
	reader->i += 1;
	line = ft_strplus(line, print_arg(reader, 4, 7, 1), 0, 1);
	line = ft_strplus(line, ", ", 1, 0);
	line = ft_strplus(line, print_arg(reader, 4, 7, 2), 1, 1);
	line = ft_strplus(line, ", ", 1, 0);
	line = ft_strplus(line, print_arg(reader, 4, 3, 3), 1, 1);
	return (line);
}

char	*ft_d_zjmp(t_read *reader)
{
	char	*line;

	line = "\nzjmp ";
	reader->i += 1;
	line = ft_strplus(line, print_dir(reader, 2), 0, 1);
	return (line);
}

char	*ft_d_ldi(t_read *reader)
{
	char	*line;

	line = "\nldi ";
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
