/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 13:38:03 by pstein            #+#    #+#             */
/*   Updated: 2020/03/15 20:19:33 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassem.h"

/*
** arg types
** DIR = 1
** INDIR = 2
** REG = 3
** DIR || INDIR = 4
** DIR || REG = 5
** INDIR || REG = 6
** DIR || INDIR || REG = 7
*/

char		*print_arg(t_read *reader, int size, int type, int num)
{
	int		bt;
	uint8_t	tr;

	bt = 8 - 2 * num;
	if ((tr = (reader->arg_types & (uint8_t)3)))
		d_errors(3);
	if ((type == 1 || type == 4 || type == 5 || type == 7)
			&& ((reader->arg_types >> bt) & (uint8_t)3) == (uint8_t)2)
		return (print_dir(reader, size));
	else if (((type == 2 || type == 4 || type == 6 || type == 7)
				&& ((reader->arg_types >> bt) & (uint8_t)3) == (uint8_t)3))
		return (print_indir(reader));
	else if (((type == 3 || type == 5 || type == 6 || type == 7)
				&& ((reader->arg_types >> bt) & (uint8_t)3) == (uint8_t)1))
		return (print_reg(reader));
	else if (type == 0 && ((reader->arg_types >> bt)
				& (uint8_t)3) == (uint8_t)0)
		return (NULL);
	return (d_errors(3));
}

int32_t		code_to_int(t_read *rd, size_t size)
{
	int32_t	result;
	_Bool	sign;
	int		i;

	result = 0;
	sign = (_Bool)(rd->code[rd->i] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((rd->code[rd->i + size - 1] ^ 0xFF) << (i++ * 8));
		else
			result += rd->code[rd->i + size - 1] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

static char	*hero_func2(t_read *reader)
{
	if (reader->code[reader->i] == 0x09)
		return (ft_d_zjmp(reader));
	else if (reader->code[reader->i] == 0x0a)
		return (ft_d_ldi(reader));
	else if (reader->code[reader->i] == 0x0b)
		return (ft_d_sti(reader));
	else if (reader->code[reader->i] == 0x0c)
		return (ft_d_fork(reader));
	else if (reader->code[reader->i] == 0x0d)
		return (ft_d_lld(reader));
	else if (reader->code[reader->i] == 0x0e)
		return (ft_d_lldi(reader));
	else if (reader->code[reader->i] == 0x0f)
		return (ft_d_lfork(reader));
	else if (reader->code[reader->i] == 0x10)
		return (ft_d_aff(reader));
	return (d_errors(3));
}

char		*hero_func(t_read *reader)
{
	if (reader->code[reader->i] == 0x01)
		return (ft_d_live(reader));
	else if (reader->code[reader->i] == 0x02)
		return (ft_d_ld(reader));
	else if (reader->code[reader->i] == 0x03)
		return (ft_d_st(reader));
	else if (reader->code[reader->i] == 0x04)
		return (ft_d_add(reader));
	else if (reader->code[reader->i] == 0x05)
		return (ft_d_sub(reader));
	else if (reader->code[reader->i] == 0x06)
		return (ft_d_and(reader));
	else if (reader->code[reader->i] == 0x07)
		return (ft_d_or(reader));
	else if (reader->code[reader->i] == 0x08)
		return (ft_d_xor(reader));
	return (hero_func2(reader));
}

void		hero_code(t_read *reader, char **code)
{
	while (reader->i < reader->code_size)
	{
		if (reader->code[reader->i] >= 0x01 && reader->code[reader->i] <= 0x10)
			*code = ft_strplus(*code, hero_func(reader), 1, 1);
		else
			d_errors(3);
	}
}
