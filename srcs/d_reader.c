/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_reader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 14:49:56 by pstein            #+#    #+#             */
/*   Updated: 2020/03/15 15:03:02 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassem.h"

static int32_t	buff_to_int(const uint8_t *bytecode, int size)
{
	int32_t	result;
	_Bool	sign;
	int		i;

	result = 0;
	sign = (_Bool)(bytecode[0] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((bytecode[size - 1] ^ 0xFF) << (i++ * 8));
		else
			result += bytecode[size - 1] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

static int32_t	read_int(int fd)
{
	int		size;
	uint8_t	buffer[4];

	size = read(fd, &buffer, 4);
	if (size == -1)
		exit(0);
	if (size < 4)
		exit(0);
	return (buff_to_int(buffer, 4));
}

static char		*read_commands(int fd, int len)
{
	int		size;
	char	*buffer;
	int		i;

	if (!(buffer = ft_strnew(len)))
		exit(0);
	size = read(fd, buffer, len);
	if (size == -1)
		exit(0);
	if (size < len)
		exit(0);
	i = ft_strlen(buffer);
	while (i < len)
	{
		if (buffer[i])
			exit(0);
		i++;
	}
	return (buffer);
}

static uint8_t	*parse_code(int fd, int len)
{
	int		size;
	uint8_t	*buffer;
	uint8_t	byte;

	if (!(buffer = ft_memalloc(len)))
		exit(0);
	size = read(fd, buffer, len);
	if (size == -1)
		exit(0);
	if (size < len || read(fd, &byte, 1) != 0)
		exit(0);
	return (buffer);
}

void			read_codefile(t_read *reader, int fd)
{
	if (read_int(fd) != COREWAR_EXEC_MAGIC)
		exit(0);
	reader->name = read_commands(fd, PROG_NAME_LENGTH);
	if (read_int(fd) != 0)
		exit(0);
	if ((reader->code_size = read_int(fd)) < 0)
		exit(0);
	reader->comment = read_commands(fd, COMMENT_LENGTH);
	if (read_int(fd) != 0)
		exit(0);
	reader->code = parse_code(fd, reader->code_size);
}
